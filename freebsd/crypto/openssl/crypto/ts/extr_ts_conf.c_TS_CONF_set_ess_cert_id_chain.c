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

/* Variables and functions */
 int /*<<< orphan*/  ENV_ESS_CERT_ID_CHAIN ; 
 int /*<<< orphan*/  TS_ESS_CERT_ID_CHAIN ; 
 int ts_CONF_add_flag (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int TS_CONF_set_ess_cert_id_chain(CONF *conf, const char *section,
                                  TS_RESP_CTX *ctx)
{
    return ts_CONF_add_flag(conf, section, ENV_ESS_CERT_ID_CHAIN,
                            TS_ESS_CERT_ID_CHAIN, ctx);
}