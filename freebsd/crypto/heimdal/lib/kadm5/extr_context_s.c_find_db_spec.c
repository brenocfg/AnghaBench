#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hdb_dbinfo {int dummy; } ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_6__ {int /*<<< orphan*/  socket_info; int /*<<< orphan*/  socket_name; int /*<<< orphan*/ * log_file; } ;
struct TYPE_5__ {int /*<<< orphan*/ * stash_file; int /*<<< orphan*/ * acl_file; int /*<<< orphan*/ * dbname; scalar_t__ realm; } ;
struct TYPE_7__ {TYPE_2__ log_context; TYPE_1__ config; int /*<<< orphan*/  context; } ;
typedef  TYPE_3__ kadm5_server_context ;
typedef  scalar_t__ kadm5_ret_t ;

/* Variables and functions */
 int /*<<< orphan*/  asprintf (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdb_db_dir (int /*<<< orphan*/ ) ; 
 char* hdb_dbinfo_get_acl_file (int /*<<< orphan*/ ,struct hdb_dbinfo*) ; 
 char* hdb_dbinfo_get_dbname (int /*<<< orphan*/ ,struct hdb_dbinfo*) ; 
 char* hdb_dbinfo_get_log_file (int /*<<< orphan*/ ,struct hdb_dbinfo*) ; 
 char* hdb_dbinfo_get_mkey_file (int /*<<< orphan*/ ,struct hdb_dbinfo*) ; 
 struct hdb_dbinfo* hdb_dbinfo_get_next (struct hdb_dbinfo*,struct hdb_dbinfo*) ; 
 char* hdb_dbinfo_get_realm (int /*<<< orphan*/ ,struct hdb_dbinfo*) ; 
 char const* hdb_default_db (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdb_free_dbinfo (int /*<<< orphan*/ ,struct hdb_dbinfo**) ; 
 scalar_t__ hdb_get_dbinfo (int /*<<< orphan*/ ,struct hdb_dbinfo**) ; 
 int /*<<< orphan*/  set_socket_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_socket_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 
 void* strdup (char const*) ; 

__attribute__((used)) static kadm5_ret_t
find_db_spec(kadm5_server_context *ctx)
{
    krb5_context context = ctx->context;
    struct hdb_dbinfo *info, *d;
    krb5_error_code ret;

    if (ctx->config.realm) {
	/* fetch the databases */
	ret = hdb_get_dbinfo(context, &info);
	if (ret)
	    return ret;

	d = NULL;
	while ((d = hdb_dbinfo_get_next(info, d)) != NULL) {
	    const char *p = hdb_dbinfo_get_realm(context, d);

	    /* match default (realm-less) */
	    if(p != NULL && strcmp(ctx->config.realm, p) != 0)
		continue;

	    p = hdb_dbinfo_get_dbname(context, d);
	    if (p)
		ctx->config.dbname = strdup(p);

	    p = hdb_dbinfo_get_acl_file(context, d);
	    if (p)
		ctx->config.acl_file = strdup(p);

	    p = hdb_dbinfo_get_mkey_file(context, d);
	    if (p)
		ctx->config.stash_file = strdup(p);

	    p = hdb_dbinfo_get_log_file(context, d);
	    if (p)
		ctx->log_context.log_file = strdup(p);
	    break;
	}
	hdb_free_dbinfo(context, &info);
    }

    /* If any of the values was unset, pick up the default value */

    if (ctx->config.dbname == NULL)
	ctx->config.dbname = strdup(hdb_default_db(context));
    if (ctx->config.acl_file == NULL)
	asprintf(&ctx->config.acl_file, "%s/kadmind.acl", hdb_db_dir(context));
    if (ctx->config.stash_file == NULL)
	asprintf(&ctx->config.stash_file, "%s/m-key", hdb_db_dir(context));
    if (ctx->log_context.log_file == NULL)
	asprintf(&ctx->log_context.log_file, "%s/log", hdb_db_dir(context));

#ifndef NO_UNIX_SOCKETS
    set_socket_name(context, &ctx->log_context.socket_name);
#else
    set_socket_info(context, &ctx->log_context.socket_info);
#endif

    return 0;
}