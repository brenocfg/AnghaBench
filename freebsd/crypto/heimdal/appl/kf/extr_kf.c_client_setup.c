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
struct servent {int s_port; } ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  KF_PORT_NAME ; 
 int /*<<< orphan*/  KF_PORT_NUM ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  forwardable ; 
 scalar_t__ getarg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char**,int*) ; 
 scalar_t__ help_flag ; 
 int htons (int) ; 
 int /*<<< orphan*/  krb5_config_get_bool (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int krb5_getportbyname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int krb5_init_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  num_args ; 
 char* port_str ; 
 int /*<<< orphan*/  print_version (int /*<<< orphan*/ *) ; 
 struct servent* roken_getservbyname (char*,char*) ; 
 int /*<<< orphan*/  setprogname (char*) ; 
 int strtol (char*,char**,int) ; 
 int /*<<< orphan*/  usage (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ version_flag ; 

__attribute__((used)) static int
client_setup(krb5_context *context, int *argc, char **argv)
{
    int optind = 0;
    int port = 0;
    int status;

    setprogname (argv[0]);

    status = krb5_init_context (context);
    if (status)
	errx(1, "krb5_init_context failed: %d", status);

    forwardable = krb5_config_get_bool (*context, NULL,
					"libdefaults",
					"forwardable",
					NULL);

    if (getarg (args, num_args, *argc, argv, &optind))
	usage(1, args, num_args);

    if(help_flag)
	usage (0, args, num_args);
    if(version_flag) {
	print_version(NULL);
	exit(0);
    }

    if(port_str) {
	struct servent *s = roken_getservbyname(port_str, "tcp");
	if(s)
	    port = s->s_port;
	else {
	    char *ptr;

	    port = strtol (port_str, &ptr, 10);
	    if (port == 0 && ptr == port_str)
		errx (1, "Bad port `%s'", port_str);
	    port = htons(port);
	}
    }

    if (port == 0)
	port = krb5_getportbyname (*context, KF_PORT_NAME, "tcp", KF_PORT_NUM);

    if(*argc - optind < 1)
        usage(1, args, num_args);
    *argc = optind;

    return port;
}