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
typedef  int /*<<< orphan*/  krb5_log_facility ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_AUTH ; 
 int LOG_ODELAY ; 
 int LOG_PID ; 
 int /*<<< orphan*/  closelog () ; 
 int /*<<< orphan*/  context ; 
 int doit (int,int /*<<< orphan*/ ) ; 
 int execl (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,int,char*) ; 
 int krb5_openlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 int krb5_set_warn_dest (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_tkfile ; 
 int /*<<< orphan*/ * regpag_str ; 
 int /*<<< orphan*/  roken_openlog (char*,int,int /*<<< orphan*/ ) ; 
 int server_setup (int /*<<< orphan*/ *,int,char**) ; 
 int /*<<< orphan*/  service ; 
 int /*<<< orphan*/  setprogname (char*) ; 

int
main(int argc, char **argv)
{
    int port;
    int ret;
    krb5_log_facility *fac;

    setprogname (argv[0]);
    roken_openlog (argv[0], LOG_ODELAY | LOG_PID,LOG_AUTH);
    port = server_setup(&context, argc, argv);
    ret = krb5_openlog(context, "kfd", &fac);
    if(ret) krb5_err(context, 1, ret, "krb5_openlog");
    ret = krb5_set_warn_dest(context, fac);
    if(ret) krb5_err(context, 1, ret, "krb5_set_warn_dest");

    ret = doit (port, service);
    closelog();
    if (ret == 0 && regpag_str != NULL)
        ret = execl(regpag_str, "regpag", "-t", krb5_tkfile, "-r", NULL);
    return ret;
}