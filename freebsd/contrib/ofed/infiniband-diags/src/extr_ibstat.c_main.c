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
struct ibdiag_opt {char* member_0; char member_1; char* member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_2; } ;
typedef  int /*<<< orphan*/  names ;

/* Variables and functions */
 int /*<<< orphan*/  IBPANIC (char*,...) ; 
 int UMAD_CA_NAME_LEN ; 
 int UMAD_MAX_DEVICES ; 
 scalar_t__ ca_stat (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibdiag_process_opts (int,char**,int /*<<< orphan*/ *,char*,struct ibdiag_opt const*,int /*<<< orphan*/ ,char*,char const**) ; 
 scalar_t__ list_only ; 
 scalar_t__ list_ports ; 
 scalar_t__ optind ; 
 scalar_t__ ports_list (char**,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  process_opt ; 
 int /*<<< orphan*/  short_format ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int strtol (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int umad_get_cas_names (char**,int) ; 
 scalar_t__ umad_init () ; 

int main(int argc, char *argv[])
{
	char names[UMAD_MAX_DEVICES][UMAD_CA_NAME_LEN];
	int dev_port = -1;
	int n, i;

	const struct ibdiag_opt opts[] = {
		{"list_of_cas", 'l', 0, NULL, "list all IB devices"},
		{"short", 's', 0, NULL, "short output"},
		{"port_list", 'p', 0, NULL, "show port list"},
		{0}
	};
	char usage_args[] = "<ca_name> [portnum]";
	const char *usage_examples[] = {
		"-l       # list all IB devices",
		"mthca0 2 # stat port 2 of 'mthca0'",
		NULL
	};

	ibdiag_process_opts(argc, argv, NULL, "CDeGKLPsty", opts, process_opt,
			    usage_args, usage_examples);

	argc -= optind;
	argv += optind;

	if (argc > 1)
		dev_port = strtol(argv[1], 0, 0);

	if (umad_init() < 0)
		IBPANIC("can't init UMAD library");

	if ((n = umad_get_cas_names(names, UMAD_MAX_DEVICES)) < 0)
		IBPANIC("can't list IB device names");

	if (argc) {
		for (i = 0; i < n; i++)
			if (!strncmp(names[i], argv[0], sizeof names[i]))
				break;
		if (i >= n)
			IBPANIC("'%s' IB device can't be found", argv[0]);

		strncpy(names[0], argv[0], sizeof(names[0])-1);
		names[0][sizeof(names[0])-1] = '\0';
		n = 1;
	}

	if (list_ports) {
		if (ports_list(names, n) < 0)
			IBPANIC("can't list ports");
		return 0;
	}

	for (i = 0; i < n; i++) {
		if (list_only)
			printf("%s\n", names[i]);
		else if (ca_stat(names[i], dev_port, short_format) < 0)
			IBPANIC("stat of IB device '%s' failed", names[i]);
	}

	return 0;
}