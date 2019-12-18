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
typedef  int /*<<< orphan*/  random_bytes ;
typedef  int /*<<< orphan*/  private_bytes ;
typedef  int /*<<< orphan*/  done ;
typedef  int /*<<< orphan*/  SHA512_CTX ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_F_BN_GENERATE_DSA_NONCE ; 
 int /*<<< orphan*/  BN_R_PRIVATE_KEY_TOO_LARGE ; 
 int /*<<< orphan*/  BN_bin2bn (unsigned char*,unsigned int const,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_bn2binpad (int /*<<< orphan*/  const*,unsigned char*,int) ; 
 int BN_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int BN_num_bytes (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (unsigned int const) ; 
 int RAND_priv_bytes (unsigned char*,int) ; 
 int SHA512_DIGEST_LENGTH ; 
 int /*<<< orphan*/  SHA512_Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA512_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA512_Update (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,unsigned int) ; 

int BN_generate_dsa_nonce(BIGNUM *out, const BIGNUM *range,
                          const BIGNUM *priv, const unsigned char *message,
                          size_t message_len, BN_CTX *ctx)
{
    SHA512_CTX sha;
    /*
     * We use 512 bits of random data per iteration to ensure that we have at
     * least |range| bits of randomness.
     */
    unsigned char random_bytes[64];
    unsigned char digest[SHA512_DIGEST_LENGTH];
    unsigned done, todo;
    /* We generate |range|+8 bytes of random output. */
    const unsigned num_k_bytes = BN_num_bytes(range) + 8;
    unsigned char private_bytes[96];
    unsigned char *k_bytes;
    int ret = 0;

    k_bytes = OPENSSL_malloc(num_k_bytes);
    if (k_bytes == NULL)
        goto err;

    /* We copy |priv| into a local buffer to avoid exposing its length. */
    if (BN_bn2binpad(priv, private_bytes, sizeof(private_bytes)) < 0) {
        /*
         * No reasonable DSA or ECDSA key should have a private key this
         * large and we don't handle this case in order to avoid leaking the
         * length of the private key.
         */
        BNerr(BN_F_BN_GENERATE_DSA_NONCE, BN_R_PRIVATE_KEY_TOO_LARGE);
        goto err;
    }

    for (done = 0; done < num_k_bytes;) {
        if (RAND_priv_bytes(random_bytes, sizeof(random_bytes)) != 1)
            goto err;
        SHA512_Init(&sha);
        SHA512_Update(&sha, &done, sizeof(done));
        SHA512_Update(&sha, private_bytes, sizeof(private_bytes));
        SHA512_Update(&sha, message, message_len);
        SHA512_Update(&sha, random_bytes, sizeof(random_bytes));
        SHA512_Final(digest, &sha);

        todo = num_k_bytes - done;
        if (todo > SHA512_DIGEST_LENGTH)
            todo = SHA512_DIGEST_LENGTH;
        memcpy(k_bytes + done, digest, todo);
        done += todo;
    }

    if (!BN_bin2bn(k_bytes, num_k_bytes, out))
        goto err;
    if (BN_mod(out, out, range, ctx) != 1)
        goto err;
    ret = 1;

 err:
    OPENSSL_free(k_bytes);
    OPENSSL_cleanse(private_bytes, sizeof(private_bytes));
    return ret;
}