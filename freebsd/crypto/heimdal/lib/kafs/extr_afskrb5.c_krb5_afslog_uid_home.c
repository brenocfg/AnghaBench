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
typedef  int /*<<< orphan*/  uid_t ;
struct krb5_kafs_data {int /*<<< orphan*/ * context; int /*<<< orphan*/ * id; int /*<<< orphan*/  realm; } ;
struct kafs_data {char* name; struct krb5_kafs_data* data; int /*<<< orphan*/  free_error; int /*<<< orphan*/  get_error; int /*<<< orphan*/  get_realm; int /*<<< orphan*/  get_cred; scalar_t__ (* afslog_uid ) (struct kafs_data*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ;} ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/ * krb5_context ;
typedef  int /*<<< orphan*/  krb5_const_realm ;
typedef  int /*<<< orphan*/ * krb5_ccache ;

/* Variables and functions */
 scalar_t__ afslog_uid_int (struct kafs_data*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free_error ; 
 int /*<<< orphan*/  get_cred ; 
 int /*<<< orphan*/  get_error ; 
 int /*<<< orphan*/  get_realm ; 
 int /*<<< orphan*/  krb5_cc_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_default (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_init_context (int /*<<< orphan*/ **) ; 

krb5_error_code
krb5_afslog_uid_home(krb5_context context,
		     krb5_ccache id,
		     const char *cell,
		     krb5_const_realm realm,
		     uid_t uid,
		     const char *homedir)
{
    struct kafs_data kd;
    struct krb5_kafs_data d;
    krb5_error_code ret;

    kd.name = "krb5";
    kd.afslog_uid = afslog_uid_int;
    kd.get_cred = get_cred;
    kd.get_realm = get_realm;
    kd.get_error = get_error;
    kd.free_error = free_error;
    kd.data = &d;
    if (context == NULL) {
	ret = krb5_init_context(&d.context);
	if (ret)
	    return ret;
    } else
	d.context = context;
    if (id == NULL) {
	ret = krb5_cc_default(d.context, &d.id);
	if (ret)
	    goto out;
    } else
	d.id = id;
    d.realm = realm;
    ret = afslog_uid_int(&kd, cell, 0, uid, homedir);
    if (id == NULL)
	krb5_cc_close(context, d.id);
 out:
    if (context == NULL)
	krb5_free_context(d.context);
    return ret;
}