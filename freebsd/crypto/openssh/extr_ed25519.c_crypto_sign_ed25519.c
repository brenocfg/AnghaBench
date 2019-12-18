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
typedef  int /*<<< orphan*/  sc25519 ;
typedef  int /*<<< orphan*/  ge25519 ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_hash_sha512 (unsigned char*,unsigned char const*,unsigned long long) ; 
 int crypto_hash_sha512_BYTES ; 
 int /*<<< orphan*/  ge25519_pack (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_scalarmult_base (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_hram (unsigned char*,unsigned char*,unsigned char const*,unsigned char*,unsigned long long) ; 
 int /*<<< orphan*/  sc25519_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sc25519_from32bytes (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  sc25519_from64bytes (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  sc25519_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sc25519_to32bytes (unsigned char*,int /*<<< orphan*/ *) ; 

int crypto_sign_ed25519(
    unsigned char *sm,unsigned long long *smlen,
    const unsigned char *m,unsigned long long mlen,
    const unsigned char *sk
    )
{
  sc25519 sck, scs, scsk;
  ge25519 ger;
  unsigned char r[32];
  unsigned char s[32];
  unsigned char extsk[64];
  unsigned long long i;
  unsigned char hmg[crypto_hash_sha512_BYTES];
  unsigned char hram[crypto_hash_sha512_BYTES];

  crypto_hash_sha512(extsk, sk, 32);
  extsk[0] &= 248;
  extsk[31] &= 127;
  extsk[31] |= 64;

  *smlen = mlen+64;
  for(i=0;i<mlen;i++)
    sm[64 + i] = m[i];
  for(i=0;i<32;i++)
    sm[32 + i] = extsk[32+i];

  crypto_hash_sha512(hmg, sm+32, mlen+32); /* Generate k as h(extsk[32],...,extsk[63],m) */

  /* Computation of R */
  sc25519_from64bytes(&sck, hmg);
  ge25519_scalarmult_base(&ger, &sck);
  ge25519_pack(r, &ger);
  
  /* Computation of s */
  for(i=0;i<32;i++)
    sm[i] = r[i];

  get_hram(hram, sm, sk+32, sm, mlen+64);

  sc25519_from64bytes(&scs, hram);
  sc25519_from32bytes(&scsk, extsk);
  sc25519_mul(&scs, &scs, &scsk);
  
  sc25519_add(&scs, &scs, &sck);

  sc25519_to32bytes(s,&scs); /* cat s */
  for(i=0;i<32;i++)
    sm[32 + i] = s[i]; 

  return 0;
}