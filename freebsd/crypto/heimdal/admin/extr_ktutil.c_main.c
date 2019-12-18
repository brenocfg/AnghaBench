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
typedef  int krb5_error_code ;

/* Variables and functions */
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  commands ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  errx (int,char*,int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ getarg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char**,int*) ; 
 scalar_t__ help_flag ; 
 int krb5_init_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  num_args ; 
 int /*<<< orphan*/  print_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setprogname (char*) ; 
 int sl_command (int /*<<< orphan*/ ,int,char**) ; 
 int /*<<< orphan*/  usage (int) ; 
 scalar_t__ version_flag ; 

int
main(int argc, char **argv)
{
    int optidx = 0;
    krb5_error_code ret;
    setprogname(argv[0]);
    ret = krb5_init_context(&context);
    if (ret)
	errx (1, "krb5_init_context failed: %d", ret);
    if(getarg(args, num_args, argc, argv, &optidx))
	usage(1);
    if(help_flag)
	usage(0);
    if(version_flag) {
	print_version(NULL);
	exit(0);
    }
    argc -= optidx;
    argv += optidx;
    if(argc == 0)
	usage(1);
    ret = sl_command(commands, argc, argv);
    if(ret == -1)
	krb5_warnx (context, "unrecognized command: %s", argv[0]);
    return ret;
}