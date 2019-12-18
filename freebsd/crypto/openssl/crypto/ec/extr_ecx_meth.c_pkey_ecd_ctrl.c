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
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  EC_F_PKEY_ECD_CTRL ; 
 int /*<<< orphan*/  EC_R_INVALID_DIGEST_TYPE ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  EVP_PKEY_CTRL_DIGESTINIT 129 
#define  EVP_PKEY_CTRL_MD 128 
 int /*<<< orphan*/  const* EVP_md_null () ; 

__attribute__((used)) static int pkey_ecd_ctrl(EVP_PKEY_CTX *ctx, int type, int p1, void *p2)
{
    switch (type) {
    case EVP_PKEY_CTRL_MD:
        /* Only NULL allowed as digest */
        if (p2 == NULL || (const EVP_MD *)p2 == EVP_md_null())
            return 1;
        ECerr(EC_F_PKEY_ECD_CTRL, EC_R_INVALID_DIGEST_TYPE);
        return 0;

    case EVP_PKEY_CTRL_DIGESTINIT:
        return 1;
    }
    return -2;
}