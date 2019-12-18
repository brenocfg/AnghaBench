#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  logf; } ;
typedef  TYPE_1__ krb5_kdc_configuration ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  KDC_LOG_FILE ; 
 scalar_t__ asprintf (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hdb_db_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_addlog_dest (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  krb5_config_free_strings (char**) ; 
 char** krb5_config_get_strings (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_initlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_set_warn_dest (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
kdc_openlog(krb5_context context,
	    const char *service,
	    krb5_kdc_configuration *config)
{
    char **s = NULL, **p;
    krb5_initlog(context, "kdc", &config->logf);
    s = krb5_config_get_strings(context, NULL, service, "logging", NULL);
    if(s == NULL)
	s = krb5_config_get_strings(context, NULL, "logging", service, NULL);
    if(s){
	for(p = s; *p; p++)
	    krb5_addlog_dest(context, config->logf, *p);
	krb5_config_free_strings(s);
    }else {
	char *ss;
	if (asprintf(&ss, "0-1/FILE:%s/%s", hdb_db_dir(context),
	    KDC_LOG_FILE) < 0)
	    err(1, NULL);
	krb5_addlog_dest(context, config->logf, ss);
	free(ss);
    }
    krb5_set_warn_dest(context, config->logf);
}