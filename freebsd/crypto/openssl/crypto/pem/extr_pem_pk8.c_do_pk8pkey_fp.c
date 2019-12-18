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
typedef  int /*<<< orphan*/  pem_password_cb ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_NOCLOSE ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_fp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BUF_LIB ; 
 int /*<<< orphan*/  PEM_F_DO_PK8PKEY_FP ; 
 int /*<<< orphan*/  PEMerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int do_pk8pkey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/  const*,char*,int,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int do_pk8pkey_fp(FILE *fp, EVP_PKEY *x, int isder, int nid,
                         const EVP_CIPHER *enc, char *kstr, int klen,
                         pem_password_cb *cb, void *u)
{
    BIO *bp;
    int ret;

    if ((bp = BIO_new_fp(fp, BIO_NOCLOSE)) == NULL) {
        PEMerr(PEM_F_DO_PK8PKEY_FP, ERR_R_BUF_LIB);
        return 0;
    }
    ret = do_pk8pkey(bp, x, isder, nid, enc, kstr, klen, cb, u);
    BIO_free(bp);
    return ret;
}