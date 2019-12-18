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
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_F_ECKEY_PARAM_DECODE ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_EC_LIB ; 
 int /*<<< orphan*/  EVP_PKEY_assign_EC_KEY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_ECParameters (int /*<<< orphan*/ *,unsigned char const**,int) ; 

__attribute__((used)) static int eckey_param_decode(EVP_PKEY *pkey,
                              const unsigned char **pder, int derlen)
{
    EC_KEY *eckey;

    if ((eckey = d2i_ECParameters(NULL, pder, derlen)) == NULL) {
        ECerr(EC_F_ECKEY_PARAM_DECODE, ERR_R_EC_LIB);
        return 0;
    }
    EVP_PKEY_assign_EC_KEY(pkey, eckey);
    return 1;
}