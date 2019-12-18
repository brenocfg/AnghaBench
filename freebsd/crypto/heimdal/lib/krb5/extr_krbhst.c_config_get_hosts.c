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
struct krb5_krbhst_data {int /*<<< orphan*/  port; int /*<<< orphan*/  def_port; int /*<<< orphan*/  flags; int /*<<< orphan*/  realm; } ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  KD_CONFIG_EXISTS ; 
 int /*<<< orphan*/  _krb5_debug (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  append_host_string (int /*<<< orphan*/ ,struct krb5_krbhst_data*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_config_free_strings (char**) ; 
 char** krb5_config_get_strings (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
config_get_hosts(krb5_context context, struct krb5_krbhst_data *kd,
		 const char *conf_string)
{
    int i;
    char **hostlist;
    hostlist = krb5_config_get_strings(context, NULL,
				       "realms", kd->realm, conf_string, NULL);

    _krb5_debug(context, 2, "configuration file for realm %s%s found",
		kd->realm, hostlist ? "" : " not");

    if(hostlist == NULL)
	return;
    kd->flags |= KD_CONFIG_EXISTS;
    for(i = 0; hostlist && hostlist[i] != NULL; i++)
	append_host_string(context, kd, hostlist[i], kd->def_port, kd->port);

    krb5_config_free_strings(hostlist);
}