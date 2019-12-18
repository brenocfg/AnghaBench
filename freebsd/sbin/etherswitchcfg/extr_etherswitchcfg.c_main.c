#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  es_nvlangroups; int /*<<< orphan*/  es_nports; } ;
struct cfg {char* controlfile; scalar_t__ fd; int mode; TYPE_1__ info; int /*<<< orphan*/  unit; TYPE_1__ conf; int /*<<< orphan*/  verbose; int /*<<< orphan*/  mediatypes; } ;
typedef  int /*<<< orphan*/  cfg ;
struct TYPE_4__ {char* name; int mode; int args; int (* f ) (struct cfg*,int,char**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  IOETHERSWITCHGETCONF ; 
 int /*<<< orphan*/  IOETHERSWITCHGETINFO ; 
#define  MODE_ATU 134 
#define  MODE_CONFIG 133 
#define  MODE_NONE 132 
#define  MODE_PHYREG 131 
#define  MODE_PORT 130 
#define  MODE_REGISTER 129 
#define  MODE_VLANGROUP 128 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  bzero (struct cfg*,int) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 TYPE_2__* cmds ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char*) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ ioctl (scalar_t__,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  newmode (struct cfg*,int const) ; 
 scalar_t__ open (char*,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  print_info (struct cfg*) ; 
 int /*<<< orphan*/  printf (char*,char*,int,char*) ; 
 int /*<<< orphan*/  set_phyregister (struct cfg*,char*) ; 
 int /*<<< orphan*/  set_register (struct cfg*,char*) ; 
 int sscanf (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int stub1 (struct cfg*,int,char**) ; 
 int /*<<< orphan*/  usage (struct cfg*,char**) ; 

int
main(int argc, char *argv[])
{
	int ch;
	struct cfg cfg;
	int i;
	
	bzero(&cfg, sizeof(cfg));
	cfg.controlfile = "/dev/etherswitch0";
	while ((ch = getopt(argc, argv, "f:mv?")) != -1)
		switch(ch) {
		case 'f':
			cfg.controlfile = optarg;
			break;
		case 'm':
			cfg.mediatypes++;
			break;
		case 'v':
			cfg.verbose++;
			break;
		case '?':
			/* FALLTHROUGH */
		default:
			usage(&cfg, argv);
		}
	argc -= optind;
	argv += optind;
	cfg.fd = open(cfg.controlfile, O_RDONLY);
	if (cfg.fd < 0)
		err(EX_UNAVAILABLE, "Can't open control file: %s", cfg.controlfile);
	if (ioctl(cfg.fd, IOETHERSWITCHGETINFO, &cfg.info) != 0)
		err(EX_OSERR, "ioctl(IOETHERSWITCHGETINFO)");
	if (ioctl(cfg.fd, IOETHERSWITCHGETCONF, &cfg.conf) != 0)
		err(EX_OSERR, "ioctl(IOETHERSWITCHGETCONF)");
	if (argc == 0) {
		print_info(&cfg);
		return (0);
	}
	cfg.mode = MODE_NONE;
	while (argc > 0) {
		switch(cfg.mode) {
		case MODE_NONE:
			if (strcmp(argv[0], "info") == 0) {
				print_info(&cfg);
			} else if (sscanf(argv[0], "port%d", &cfg.unit) == 1) {
				if (cfg.unit < 0 || cfg.unit >= cfg.info.es_nports)
					errx(EX_USAGE, "port unit must be between 0 and %d", cfg.info.es_nports - 1);
				newmode(&cfg, MODE_PORT);
			} else if (sscanf(argv[0], "vlangroup%d", &cfg.unit) == 1) {
				if (cfg.unit < 0 || cfg.unit >= cfg.info.es_nvlangroups)
					errx(EX_USAGE,
					    "vlangroup unit must be between 0 and %d",
					    cfg.info.es_nvlangroups - 1);
				newmode(&cfg, MODE_VLANGROUP);
			} else if (strcmp(argv[0], "config") == 0) {
				newmode(&cfg, MODE_CONFIG);
			} else if (strcmp(argv[0], "phy") == 0) {
				newmode(&cfg, MODE_PHYREG);
			} else if (strcmp(argv[0], "reg") == 0) {
				newmode(&cfg, MODE_REGISTER);
			} else if (strcmp(argv[0], "help") == 0) {
				usage(&cfg, argv);
			} else if (strcmp(argv[0], "atu") == 0) {
				newmode(&cfg, MODE_ATU);
			} else {
				errx(EX_USAGE, "Unknown command \"%s\"", argv[0]);
			}
			break;
		case MODE_PORT:
		case MODE_CONFIG:
		case MODE_VLANGROUP:
		case MODE_ATU:
			for(i=0; cmds[i].name != NULL; i++) {
				int r;
				if (cfg.mode == cmds[i].mode &&
				    strcmp(argv[0], cmds[i].name) == 0) {
					if ((cmds[i].args != -1) &&
					    (argc < (cmds[i].args + 1))) {
						printf("%s needs %d argument%s\n",
						    cmds[i].name, cmds[i].args,
						    (cmds[i].args==1)?"":",");
						break;
					}

					r = (cmds[i].f)(&cfg, argc, argv);

					/* -1 here means "error" */
					if (r == -1) {
						argc = 0;
						break;
					}

					/* Legacy return value */
					if (r == 0)
						r = cmds[i].args;

					argc -= r;
					argv += r;
					break;
				}
			}
			if (cmds[i].name == NULL) {
				newmode(&cfg, MODE_NONE);
				continue;
			}
			break;
		case MODE_REGISTER:
			if (set_register(&cfg, argv[0]) != 0) {
				newmode(&cfg, MODE_NONE);
				continue;
			}
			break;
		case MODE_PHYREG:
			if (set_phyregister(&cfg, argv[0]) != 0) {
				newmode(&cfg, MODE_NONE);
				continue;
			}
			break;
		}
		argc--;
		argv++;
	}
	/* switch back to command mode to print configuration for last command */
	newmode(&cfg, MODE_NONE);
	close(cfg.fd);
	return (0);
}