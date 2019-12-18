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
typedef  int /*<<< orphan*/  CONF ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OBJECT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENV_DEFAULT_POLICY ; 
 char* NCONF_get_string (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OBJ_txt2obj (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_RESP_CTX_set_def_policy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_CONF_invalid (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_CONF_lookup_fail (char const*,int /*<<< orphan*/ ) ; 

int TS_CONF_set_def_policy(CONF *conf, const char *section,
                           const char *policy, TS_RESP_CTX *ctx)
{
    int ret = 0;
    ASN1_OBJECT *policy_obj = NULL;
    if (!policy)
        policy = NCONF_get_string(conf, section, ENV_DEFAULT_POLICY);
    if (!policy) {
        ts_CONF_lookup_fail(section, ENV_DEFAULT_POLICY);
        goto err;
    }
    if ((policy_obj = OBJ_txt2obj(policy, 0)) == NULL) {
        ts_CONF_invalid(section, ENV_DEFAULT_POLICY);
        goto err;
    }
    if (!TS_RESP_CTX_set_def_policy(ctx, policy_obj))
        goto err;

    ret = 1;
 err:
    ASN1_OBJECT_free(policy_obj);
    return ret;
}