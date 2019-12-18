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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int EVP_MD_block_size (int /*<<< orphan*/  const*) ; 
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  PKCS12_F_PKCS12_KEY_GEN_UNI ; 
 int /*<<< orphan*/  PKCS12err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  h__dump (unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  stderr ; 

int PKCS12_key_gen_uni(unsigned char *pass, int passlen, unsigned char *salt,
                       int saltlen, int id, int iter, int n,
                       unsigned char *out, const EVP_MD *md_type)
{
    unsigned char *B = NULL, *D = NULL, *I = NULL, *p = NULL, *Ai = NULL;
    int Slen, Plen, Ilen;
    int i, j, u, v;
    int ret = 0;
    EVP_MD_CTX *ctx = NULL;
#ifdef  OPENSSL_DEBUG_KEYGEN
    unsigned char *tmpout = out;
    int tmpn = n;
#endif

    ctx = EVP_MD_CTX_new();
    if (ctx == NULL)
        goto err;

#ifdef  OPENSSL_DEBUG_KEYGEN
    fprintf(stderr, "KEYGEN DEBUG\n");
    fprintf(stderr, "ID %d, ITER %d\n", id, iter);
    fprintf(stderr, "Password (length %d):\n", passlen);
    h__dump(pass, passlen);
    fprintf(stderr, "Salt (length %d):\n", saltlen);
    h__dump(salt, saltlen);
#endif
    v = EVP_MD_block_size(md_type);
    u = EVP_MD_size(md_type);
    if (u < 0 || v <= 0)
        goto err;
    D = OPENSSL_malloc(v);
    Ai = OPENSSL_malloc(u);
    B = OPENSSL_malloc(v + 1);
    Slen = v * ((saltlen + v - 1) / v);
    if (passlen)
        Plen = v * ((passlen + v - 1) / v);
    else
        Plen = 0;
    Ilen = Slen + Plen;
    I = OPENSSL_malloc(Ilen);
    if (D == NULL || Ai == NULL || B == NULL || I == NULL)
        goto err;
    for (i = 0; i < v; i++)
        D[i] = id;
    p = I;
    for (i = 0; i < Slen; i++)
        *p++ = salt[i % saltlen];
    for (i = 0; i < Plen; i++)
        *p++ = pass[i % passlen];
    for (;;) {
        if (!EVP_DigestInit_ex(ctx, md_type, NULL)
            || !EVP_DigestUpdate(ctx, D, v)
            || !EVP_DigestUpdate(ctx, I, Ilen)
            || !EVP_DigestFinal_ex(ctx, Ai, NULL))
            goto err;
        for (j = 1; j < iter; j++) {
            if (!EVP_DigestInit_ex(ctx, md_type, NULL)
                || !EVP_DigestUpdate(ctx, Ai, u)
                || !EVP_DigestFinal_ex(ctx, Ai, NULL))
                goto err;
        }
        memcpy(out, Ai, min(n, u));
        if (u >= n) {
#ifdef OPENSSL_DEBUG_KEYGEN
            fprintf(stderr, "Output KEY (length %d)\n", tmpn);
            h__dump(tmpout, tmpn);
#endif
            ret = 1;
            goto end;
        }
        n -= u;
        out += u;
        for (j = 0; j < v; j++)
            B[j] = Ai[j % u];
        for (j = 0; j < Ilen; j += v) {
            int k;
            unsigned char *Ij = I + j;
            uint16_t c = 1;

            /* Work out Ij = Ij + B + 1 */
            for (k = v - 1; k >= 0; k--) {
                c += Ij[k] + B[k];
                Ij[k] = (unsigned char)c;
                c >>= 8;
            }
        }
    }

 err:
    PKCS12err(PKCS12_F_PKCS12_KEY_GEN_UNI, ERR_R_MALLOC_FAILURE);

 end:
    OPENSSL_free(Ai);
    OPENSSL_free(B);
    OPENSSL_free(D);
    OPENSSL_free(I);
    EVP_MD_CTX_free(ctx);
    return ret;
}