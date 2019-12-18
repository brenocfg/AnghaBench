#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usage_args ;
struct TYPE_2__ {char* trap_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBEXIT (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IB_SMI_CLASS ; 
 int IB_SMI_DIRECT_CLASS ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  error_port ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  ibd_ca ; 
 int /*<<< orphan*/  ibd_ca_port ; 
 int /*<<< orphan*/  ibd_mkey ; 
 int /*<<< orphan*/  ibdiag_process_opts (int,char**,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mad_rpc_close_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mad_rpc_open_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  madrpc_show_errors (int) ; 
 scalar_t__ optind ; 
 int process_send_trap (char*) ; 
 int /*<<< orphan*/  smp_mkey_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ snprintf (char*,int,char*,char*) ; 
 int sprintf (char*,char*) ; 
 int /*<<< orphan*/  srcport ; 
 TYPE_1__* traps ; 

int main(int argc, char **argv)
{
	char usage_args[1024];
	int mgmt_classes[2] = { IB_SMI_CLASS, IB_SMI_DIRECT_CLASS };
	char *trap_name = NULL;
	int i, n, rc;

	n = sprintf(usage_args, "[<trap_name>] [<error_port>]\n"
		    "\nArgument <trap_name> can be one of the following:\n");
	for (i = 0; traps[i].trap_name; i++) {
		n += snprintf(usage_args + n, sizeof(usage_args) - n,
			      "  %s\n", traps[i].trap_name);
		if (n >= sizeof(usage_args))
			exit(-1);
	}
	snprintf(usage_args + n, sizeof(usage_args) - n,
		 "\n  default behavior is to send \"%s\"", traps[0].trap_name);

	ibdiag_process_opts(argc, argv, NULL, "DGKL", NULL, NULL,
			    usage_args, NULL);

	argc -= optind;
	argv += optind;

	trap_name = argv[0] ? argv[0] : traps[0].trap_name;

	if (argc > 1)
		error_port = atoi(argv[1]);

	madrpc_show_errors(1);

	srcport = mad_rpc_open_port(ibd_ca, ibd_ca_port, mgmt_classes, 2);
	if (!srcport)
		IBEXIT("Failed to open '%s' port '%d'", ibd_ca, ibd_ca_port);

	smp_mkey_set(srcport, ibd_mkey);

	rc = process_send_trap(trap_name);
	mad_rpc_close_port(srcport);
	return rc;
}