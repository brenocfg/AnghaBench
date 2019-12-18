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
struct pmcc_op {int op_cpu; int op_pmc; int /*<<< orphan*/  op_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int PMCC_CPU_ALL ; 
 int /*<<< orphan*/  PMCC_CPU_WILDCARD ; 
#define  PMCC_ENABLE_DISABLE 131 
#define  PMCC_LIST_STATE 130 
 int /*<<< orphan*/  PMCC_OP_DISABLE ; 
 int /*<<< orphan*/  PMCC_OP_ENABLE ; 
 int PMCC_PMC_ALL ; 
 int /*<<< orphan*/  PMCC_PMC_WILDCARD ; 
#define  PMCC_PRINT_EVENTS 129 
 int PMCC_PRINT_USAGE ; 
#define  PMCC_SHOW_STATISTICS 128 
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pmcc_op*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  head ; 
 struct pmcc_op* malloc (int) ; 
 int /*<<< orphan*/  op_next ; 
 int /*<<< orphan*/ * optarg ; 
 int /*<<< orphan*/  optopt ; 
 scalar_t__ pmc_init () ; 
 int pmcc_do_enable_disable (int /*<<< orphan*/ *) ; 
 int pmcc_do_list_events () ; 
 int pmcc_do_list_state () ; 
 int /*<<< orphan*/  pmcc_init_debug () ; 
 int pmcc_show_statistics () ; 
 int strtoul (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage_message ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

int
main(int argc, char **argv)
{
	int error, command, currentcpu, option, pmc;
	char *dummy;
	struct pmcc_op *p;

#if DEBUG
	pmcc_init_debug();
#endif

	/* parse args */

	currentcpu = PMCC_CPU_ALL;
	command    = PMCC_PRINT_USAGE;
	error      = 0;

	STAILQ_INIT(&head);

	while ((option = getopt(argc, argv, ":c:d:e:lLs")) != -1)
		switch (option) {
		case 'L':
			if (command != PMCC_PRINT_USAGE) {
				error = 1;
				break;
			}
			command = PMCC_PRINT_EVENTS;
			break;

		case 'c':
			if (command != PMCC_PRINT_USAGE &&
			    command != PMCC_ENABLE_DISABLE) {
				error = 1;
				break;
			}
			command = PMCC_ENABLE_DISABLE;

			if (*optarg == PMCC_CPU_WILDCARD)
				currentcpu = PMCC_CPU_ALL;
			else {
				currentcpu = strtoul(optarg, &dummy, 0);
				if (*dummy != '\0' || currentcpu < 0)
					errx(EX_DATAERR,
					    "\"%s\" is not a valid CPU id",
					    optarg);
			}
			break;

		case 'd':
		case 'e':
			if (command != PMCC_PRINT_USAGE &&
			    command != PMCC_ENABLE_DISABLE) {
				error = 1;
				break;
			}
			command = PMCC_ENABLE_DISABLE;

			if (*optarg == PMCC_PMC_WILDCARD)
				pmc = PMCC_PMC_ALL;
			else {
				pmc = strtoul(optarg, &dummy, 0);
				if (*dummy != '\0' || pmc < 0)
					errx(EX_DATAERR,
					    "\"%s\" is not a valid PMC id",
					    optarg);
			}

			if ((p = malloc(sizeof(*p))) == NULL)
				err(EX_SOFTWARE, "Out of memory");

			p->op_cpu = currentcpu;
			p->op_pmc = pmc;
			p->op_op  = option == 'd' ? PMCC_OP_DISABLE :
			    PMCC_OP_ENABLE;

			STAILQ_INSERT_TAIL(&head, p, op_next);
			break;

		case 'l':
			if (command != PMCC_PRINT_USAGE) {
				error = 1;
				break;
			}
			command = PMCC_LIST_STATE;
			break;

		case 's':
			if (command != PMCC_PRINT_USAGE) {
				error = 1;
				break;
			}
			command = PMCC_SHOW_STATISTICS;
			break;

		case ':':
			errx(EX_USAGE,
			    "Missing argument to option '-%c'", optopt);
			break;

		case '?':
			warnx("Unrecognized option \"-%c\"", optopt);
			errx(EX_USAGE, "%s", usage_message);
			break;

		default:
			error = 1;
			break;

		}

	if (command == PMCC_PRINT_USAGE)
		(void) errx(EX_USAGE, "%s", usage_message);

	if (error)
		exit(EX_USAGE);

	if (pmc_init() < 0)
		err(EX_UNAVAILABLE,
		    "Initialization of the pmc(3) library failed");

	switch (command) {
	case PMCC_LIST_STATE:
		error = pmcc_do_list_state();
		break;
	case PMCC_PRINT_EVENTS:
		error = pmcc_do_list_events();
		break;
	case PMCC_SHOW_STATISTICS:
		error = pmcc_show_statistics();
		break;
	case PMCC_ENABLE_DISABLE:
		if (STAILQ_EMPTY(&head))
			errx(EX_USAGE,
			    "No PMCs specified to enable or disable");
		error = pmcc_do_enable_disable(&head);
		break;
	default:
		assert(0);

	}

	if (error != 0)
		err(EX_OSERR, "Command failed");
	exit(0);
}