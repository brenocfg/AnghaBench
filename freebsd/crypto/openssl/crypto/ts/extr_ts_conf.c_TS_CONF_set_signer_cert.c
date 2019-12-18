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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  TS_RESP_CTX ;
typedef  int /*<<< orphan*/  CONF ;

/* Variables and functions */
 int /*<<< orphan*/  ENV_SIGNER_CERT ; 
 char* NCONF_get_string (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * TS_CONF_load_cert (char const*) ; 
 int /*<<< orphan*/  TS_RESP_CTX_set_signer_cert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_CONF_lookup_fail (char const*,int /*<<< orphan*/ ) ; 

int TS_CONF_set_signer_cert(CONF *conf, const char *section,
                            const char *cert, TS_RESP_CTX *ctx)
{
    int ret = 0;
    X509 *cert_obj = NULL;

    if (cert == NULL) {
        cert = NCONF_get_string(conf, section, ENV_SIGNER_CERT);
        if (cert == NULL) {
            ts_CONF_lookup_fail(section, ENV_SIGNER_CERT);
            goto err;
        }
    }
    if ((cert_obj = TS_CONF_load_cert(cert)) == NULL)
        goto err;
    if (!TS_RESP_CTX_set_signer_cert(ctx, cert_obj))
        goto err;

    ret = 1;
 err:
    X509_free(cert_obj);
    return ret;
}