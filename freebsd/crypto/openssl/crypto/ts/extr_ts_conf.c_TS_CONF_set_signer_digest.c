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
typedef  int /*<<< orphan*/  TS_RESP_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  CONF ;

/* Variables and functions */
 int /*<<< orphan*/  ENV_SIGNER_DIGEST ; 
 int /*<<< orphan*/ * EVP_get_digestbyname (char const*) ; 
 char* NCONF_get_string (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_RESP_CTX_set_signer_digest (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ts_CONF_invalid (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_CONF_lookup_fail (char const*,int /*<<< orphan*/ ) ; 

int TS_CONF_set_signer_digest(CONF *conf, const char *section,
                              const char *md, TS_RESP_CTX *ctx)
{
    int ret = 0;
    const EVP_MD *sign_md = NULL;
    if (md == NULL)
        md = NCONF_get_string(conf, section, ENV_SIGNER_DIGEST);
    if (md == NULL) {
        ts_CONF_lookup_fail(section, ENV_SIGNER_DIGEST);
        goto err;
    }
    sign_md = EVP_get_digestbyname(md);
    if (sign_md == NULL) {
        ts_CONF_invalid(section, ENV_SIGNER_DIGEST);
        goto err;
    }
    if (!TS_RESP_CTX_set_signer_digest(ctx, sign_md))
        goto err;

    ret = 1;
 err:
    return ret;
}