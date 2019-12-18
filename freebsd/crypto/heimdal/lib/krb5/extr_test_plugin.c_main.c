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
typedef  int /*<<< orphan*/  krb5_krbhst_handle ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  host ;

/* Variables and functions */
 int /*<<< orphan*/  KRB5_KRBHST_KDC ; 
 int /*<<< orphan*/  KRB5_PLUGIN_LOCATE ; 
 int MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  PLUGIN_TYPE_DATA ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_init_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_krbhst_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_krbhst_init_flags (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_krbhst_next_as_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ krb5_plugin_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resolve ; 
 int /*<<< orphan*/  setprogname (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

int
main(int argc, char **argv)
{
    krb5_error_code ret;
    krb5_context context;
    krb5_krbhst_handle handle;
    char host[MAXHOSTNAMELEN];
    int found = 0;

    setprogname(argv[0]);

    ret = krb5_init_context(&context);
    if (ret)
	errx(1, "krb5_init_contex");

    ret = krb5_plugin_register(context, PLUGIN_TYPE_DATA,
			       KRB5_PLUGIN_LOCATE, &resolve);
    if (ret)
	krb5_err(context, 1, ret, "krb5_plugin_register");


    ret = krb5_krbhst_init_flags(context,
				 "NOTHERE.H5L.SE",
				 KRB5_KRBHST_KDC,
				 0,
				 &handle);
    if (ret)
	krb5_err(context, 1, ret, "krb5_krbhst_init_flags");


    while(krb5_krbhst_next_as_string(context, handle, host, sizeof(host)) == 0){
	found++;
 	if (strcmp(host, "127.0.0.2") != 0)
	    krb5_errx(context, 1, "wrong address: %s", host);
    }
    if (!found)
	krb5_errx(context, 1, "failed to find host");

    krb5_krbhst_free(context, handle);

    krb5_free_context(context);
    return 0;
}