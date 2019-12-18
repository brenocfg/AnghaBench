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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  KDF_F_PKEY_SCRYPT_CTRL_UINT64 ; 
 int /*<<< orphan*/  KDF_R_VALUE_ERROR ; 
 int /*<<< orphan*/  KDFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atou64 (char const*,int /*<<< orphan*/ *) ; 
 int pkey_scrypt_ctrl (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pkey_scrypt_ctrl_uint64(EVP_PKEY_CTX *ctx, int type,
                                   const char *value)
{
    uint64_t int_value;

    if (!atou64(value, &int_value)) {
        KDFerr(KDF_F_PKEY_SCRYPT_CTRL_UINT64, KDF_R_VALUE_ERROR);
        return 0;
    }
    return pkey_scrypt_ctrl(ctx, type, 0, &int_value);
}