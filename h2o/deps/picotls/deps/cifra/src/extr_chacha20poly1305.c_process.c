#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int /*<<< orphan*/  cf_poly1305 ;
typedef  int /*<<< orphan*/  const cf_chacha20_ctx ;

/* Variables and functions */
 int ENCRYPT ; 
 int FAILURE ; 
 int PADLEN (size_t) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  cf_chacha20_cipher (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  cf_chacha20_init_custom (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  cf_poly1305_finish (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cf_poly1305_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cf_poly1305_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  mem_clean (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ mem_eq (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  write64_le (size_t,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int process(const uint8_t key[32],
                   const uint8_t nonce[12],
                   const uint8_t *header, size_t nheader,
                   const uint8_t *input, size_t nbytes,
                   uint8_t *output,
                   int mode,
                   uint8_t tag[16])
{
  /* First, generate the Poly1305 key by running ChaCha20 with the
   * given key and a zero counter.  The first half of the
   * 64-byte output is the key. */
  uint8_t fullnonce[16] = { 0 };
  memcpy(fullnonce + 4, nonce, 12);

  uint8_t polykey[32] = { 0 };
  cf_chacha20_ctx chacha;
  cf_chacha20_init_custom(&chacha, key, 32, fullnonce, 4);
  cf_chacha20_cipher(&chacha, polykey, polykey, sizeof polykey);

  /* Now initialise Poly1305. */
  cf_poly1305 poly;
  cf_poly1305_init(&poly, polykey, polykey + 16);
  mem_clean(polykey, sizeof polykey);

  /* Discard next 32 bytes of chacha20 key stream. */
  cf_chacha20_cipher(&chacha, polykey, polykey, sizeof polykey);
  mem_clean(polykey, sizeof polykey);

  /* The input to Poly1305 is:
   * AAD || pad(AAD) || cipher || pad(cipher) || len_64(aad) || len_64(cipher) */
  uint8_t padbuf[16] = { 0 };

#define PADLEN(x) (16 - ((x) & 0xf))

  /* AAD || pad(AAD) */
  cf_poly1305_update(&poly, header, nheader);
  cf_poly1305_update(&poly, padbuf, PADLEN(nheader));

  /* || cipher */
  if (mode == ENCRYPT)
  {
    /* If we're encrypting, we compute the ciphertext
     * before inputting it into the MAC. */
    cf_chacha20_cipher(&chacha, input, output, nbytes);
    cf_poly1305_update(&poly, output, nbytes);
  } else {
    /* Otherwise: decryption -- input the ciphertext.
     * Delay actual decryption until we checked the MAC. */
    cf_poly1305_update(&poly, input, nbytes);
  }

  /* || pad(cipher) */
  cf_poly1305_update(&poly, padbuf, PADLEN(nbytes));

  /* || len_64(aad) || len_64(cipher) */
  write64_le(nheader, padbuf);
  write64_le(nbytes, padbuf + 8);
  cf_poly1305_update(&poly, padbuf, sizeof padbuf);

  /* MAC computation is now complete. */

  if (mode == ENCRYPT)
  {
    cf_poly1305_finish(&poly, tag);
    mem_clean(&chacha, sizeof chacha);
    return SUCCESS;
  }

  /* Decrypt mode: calculate tag, and check it.
   * If it's correct, proceed with decryption. */
  uint8_t checktag[16];
  cf_poly1305_finish(&poly, checktag);

  if (mem_eq(checktag, tag, sizeof checktag))
  {
    cf_chacha20_cipher(&chacha, input, output, nbytes);
    mem_clean(&chacha, sizeof chacha);
    mem_clean(checktag, sizeof checktag);
    return SUCCESS;
  } else {
    mem_clean(output, nbytes);
    mem_clean(&chacha, sizeof chacha);
    mem_clean(checktag, sizeof checktag);
    return FAILURE;
  }
}