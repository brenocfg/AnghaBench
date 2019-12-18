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
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_CTRL_CIPHER ; 
 int /*<<< orphan*/  EVP_PKEY_CTRL_SET_MAC_KEY ; 
 int EVP_PKEY_CTX_hex2ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int EVP_PKEY_CTX_str2ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * EVP_get_cipherbyname (char const*) ; 
 int pkey_cmac_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,void*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int pkey_cmac_ctrl_str(EVP_PKEY_CTX *ctx,
                              const char *type, const char *value)
{
    if (!value) {
        return 0;
    }
    if (strcmp(type, "cipher") == 0) {
        const EVP_CIPHER *c;
        c = EVP_get_cipherbyname(value);
        if (!c)
            return 0;
        return pkey_cmac_ctrl(ctx, EVP_PKEY_CTRL_CIPHER, -1, (void *)c);
    }
    if (strcmp(type, "key") == 0)
        return EVP_PKEY_CTX_str2ctrl(ctx, EVP_PKEY_CTRL_SET_MAC_KEY, value);
    if (strcmp(type, "hexkey") == 0)
        return EVP_PKEY_CTX_hex2ctrl(ctx, EVP_PKEY_CTRL_SET_MAC_KEY, value);
    return -2;
}