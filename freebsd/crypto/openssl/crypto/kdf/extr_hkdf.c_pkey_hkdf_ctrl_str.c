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
 int /*<<< orphan*/  EVP_PKEY_CTRL_HKDF_INFO ; 
 int /*<<< orphan*/  EVP_PKEY_CTRL_HKDF_KEY ; 
 int /*<<< orphan*/  EVP_PKEY_CTRL_HKDF_MD ; 
 int /*<<< orphan*/  EVP_PKEY_CTRL_HKDF_SALT ; 
 int EVP_PKEY_CTX_hex2ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int EVP_PKEY_CTX_hkdf_mode (int /*<<< orphan*/ *,int) ; 
 int EVP_PKEY_CTX_md (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int EVP_PKEY_CTX_str2ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int EVP_PKEY_HKDEF_MODE_EXPAND_ONLY ; 
 int EVP_PKEY_HKDEF_MODE_EXTRACT_AND_EXPAND ; 
 int EVP_PKEY_HKDEF_MODE_EXTRACT_ONLY ; 
 int /*<<< orphan*/  EVP_PKEY_OP_DERIVE ; 
 int /*<<< orphan*/  KDF_F_PKEY_HKDF_CTRL_STR ; 
 int /*<<< orphan*/  KDF_R_UNKNOWN_PARAMETER_TYPE ; 
 int /*<<< orphan*/  KDFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int pkey_hkdf_ctrl_str(EVP_PKEY_CTX *ctx, const char *type,
                              const char *value)
{
    if (strcmp(type, "mode") == 0) {
        int mode;

        if (strcmp(value, "EXTRACT_AND_EXPAND") == 0)
            mode = EVP_PKEY_HKDEF_MODE_EXTRACT_AND_EXPAND;
        else if (strcmp(value, "EXTRACT_ONLY") == 0)
            mode = EVP_PKEY_HKDEF_MODE_EXTRACT_ONLY;
        else if (strcmp(value, "EXPAND_ONLY") == 0)
            mode = EVP_PKEY_HKDEF_MODE_EXPAND_ONLY;
        else
            return 0;

        return EVP_PKEY_CTX_hkdf_mode(ctx, mode);
    }

    if (strcmp(type, "md") == 0)
        return EVP_PKEY_CTX_md(ctx, EVP_PKEY_OP_DERIVE,
                               EVP_PKEY_CTRL_HKDF_MD, value);

    if (strcmp(type, "salt") == 0)
        return EVP_PKEY_CTX_str2ctrl(ctx, EVP_PKEY_CTRL_HKDF_SALT, value);

    if (strcmp(type, "hexsalt") == 0)
        return EVP_PKEY_CTX_hex2ctrl(ctx, EVP_PKEY_CTRL_HKDF_SALT, value);

    if (strcmp(type, "key") == 0)
        return EVP_PKEY_CTX_str2ctrl(ctx, EVP_PKEY_CTRL_HKDF_KEY, value);

    if (strcmp(type, "hexkey") == 0)
        return EVP_PKEY_CTX_hex2ctrl(ctx, EVP_PKEY_CTRL_HKDF_KEY, value);

    if (strcmp(type, "info") == 0)
        return EVP_PKEY_CTX_str2ctrl(ctx, EVP_PKEY_CTRL_HKDF_INFO, value);

    if (strcmp(type, "hexinfo") == 0)
        return EVP_PKEY_CTX_hex2ctrl(ctx, EVP_PKEY_CTRL_HKDF_INFO, value);

    KDFerr(KDF_F_PKEY_HKDF_CTRL_STR, KDF_R_UNKNOWN_PARAMETER_TYPE);
    return -2;
}