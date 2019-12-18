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
struct hdb_dbinfo {int /*<<< orphan*/  const* binding; void* log_file; void* acl_file; void* mkey_file; void* realm; void* dbname; void* label; } ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_config_binding ;

/* Variables and functions */
 int ENOMEM ; 
 struct hdb_dbinfo* calloc (int,int) ; 
 char* krb5_config_get_string (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int,char*) ; 
 void* strdup (char const*) ; 

__attribute__((used)) static int
get_dbinfo(krb5_context context,
	   const krb5_config_binding *db_binding,
	   const char *label,
	   struct hdb_dbinfo **db)
{
    struct hdb_dbinfo *di;
    const char *p;

    *db = NULL;

    p = krb5_config_get_string(context, db_binding, "dbname", NULL);
    if(p == NULL)
	return 0;

    di = calloc(1, sizeof(*di));
    if (di == NULL) {
	krb5_set_error_message(context, ENOMEM, "malloc: out of memory");
	return ENOMEM;
    }
    di->label = strdup(label);
    di->dbname = strdup(p);

    p = krb5_config_get_string(context, db_binding, "realm", NULL);
    if(p)
	di->realm = strdup(p);
    p = krb5_config_get_string(context, db_binding, "mkey_file", NULL);
    if(p)
	di->mkey_file = strdup(p);
    p = krb5_config_get_string(context, db_binding, "acl_file", NULL);
    if(p)
	di->acl_file = strdup(p);
    p = krb5_config_get_string(context, db_binding, "log_file", NULL);
    if(p)
	di->log_file = strdup(p);

    di->binding = db_binding;

    *db = di;
    return 0;
}