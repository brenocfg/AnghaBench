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

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_CTRL_PASS ; 
 int /*<<< orphan*/  EVP_PKEY_CTRL_SCRYPT_MAXMEM_BYTES ; 
 int /*<<< orphan*/  EVP_PKEY_CTRL_SCRYPT_N ; 
 int /*<<< orphan*/  EVP_PKEY_CTRL_SCRYPT_P ; 
 int /*<<< orphan*/  EVP_PKEY_CTRL_SCRYPT_R ; 
 int /*<<< orphan*/  EVP_PKEY_CTRL_SCRYPT_SALT ; 
 int EVP_PKEY_CTX_hex2ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int EVP_PKEY_CTX_str2ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  KDF_F_PKEY_SCRYPT_CTRL_STR ; 
 int /*<<< orphan*/  KDF_R_UNKNOWN_PARAMETER_TYPE ; 
 int /*<<< orphan*/  KDF_R_VALUE_MISSING ; 
 int /*<<< orphan*/  KDFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pkey_scrypt_ctrl_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int pkey_scrypt_ctrl_str(EVP_PKEY_CTX *ctx, const char *type,
                                const char *value)
{
    if (value == NULL) {
        KDFerr(KDF_F_PKEY_SCRYPT_CTRL_STR, KDF_R_VALUE_MISSING);
        return 0;
    }

    if (strcmp(type, "pass") == 0)
        return EVP_PKEY_CTX_str2ctrl(ctx, EVP_PKEY_CTRL_PASS, value);

    if (strcmp(type, "hexpass") == 0)
        return EVP_PKEY_CTX_hex2ctrl(ctx, EVP_PKEY_CTRL_PASS, value);

    if (strcmp(type, "salt") == 0)
        return EVP_PKEY_CTX_str2ctrl(ctx, EVP_PKEY_CTRL_SCRYPT_SALT, value);

    if (strcmp(type, "hexsalt") == 0)
        return EVP_PKEY_CTX_hex2ctrl(ctx, EVP_PKEY_CTRL_SCRYPT_SALT, value);

    if (strcmp(type, "N") == 0)
        return pkey_scrypt_ctrl_uint64(ctx, EVP_PKEY_CTRL_SCRYPT_N, value);

    if (strcmp(type, "r") == 0)
        return pkey_scrypt_ctrl_uint64(ctx, EVP_PKEY_CTRL_SCRYPT_R, value);

    if (strcmp(type, "p") == 0)
        return pkey_scrypt_ctrl_uint64(ctx, EVP_PKEY_CTRL_SCRYPT_P, value);

    if (strcmp(type, "maxmem_bytes") == 0)
        return pkey_scrypt_ctrl_uint64(ctx, EVP_PKEY_CTRL_SCRYPT_MAXMEM_BYTES,
                                       value);

    KDFerr(KDF_F_PKEY_SCRYPT_CTRL_STR, KDF_R_UNKNOWN_PARAMETER_TYPE);
    return -2;
}