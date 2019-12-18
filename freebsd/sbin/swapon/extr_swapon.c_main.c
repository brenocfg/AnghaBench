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
struct fstab {char* fs_mntops; char* fs_spec; int /*<<< orphan*/  fs_type; } ;

/* Variables and functions */
 int Eflag ; 
 int /*<<< orphan*/  FSTAB_SW ; 
 scalar_t__ SWAPCTL ; 
 scalar_t__ SWAPOFF ; 
 scalar_t__ SWAPON ; 
 int /*<<< orphan*/  exit (int) ; 
 struct fstab* getfsent () ; 
 int getopt (int,char**,char*) ; 
 char* getprogname () ; 
 char* optarg ; 
 int /*<<< orphan*/  optind ; 
 scalar_t__ orig_prog ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char const*) ; 
 scalar_t__ qflag ; 
 int /*<<< orphan*/  setfstab (char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 char* swap_on_off (char*,int,char*) ; 
 int /*<<< orphan*/  swaplist (int,int,int) ; 
 int /*<<< orphan*/  usage () ; 
 scalar_t__ which_prog ; 

int
main(int argc, char **argv)
{
	struct fstab *fsp;
	const char *swfile;
	char *ptr;
	int ret, ch, doall;
	int sflag, lflag, late, hflag;
	const char *etc_fstab;

	sflag = lflag = late = hflag = 0;
	if ((ptr = strrchr(argv[0], '/')) == NULL)
		ptr = argv[0];
	if (strstr(ptr, "swapon") != NULL)
		which_prog = SWAPON;
	else if (strstr(ptr, "swapoff") != NULL)
		which_prog = SWAPOFF;
	orig_prog = which_prog;
	
	doall = 0;
	etc_fstab = NULL;
	while ((ch = getopt(argc, argv, "AadEghklLmqsUF:")) != -1) {
		switch(ch) {
		case 'A':
			if (which_prog == SWAPCTL) {
				doall = 1;
				which_prog = SWAPON;
			} else
				usage();
			break;
		case 'a':
			if (which_prog == SWAPON || which_prog == SWAPOFF)
				doall = 1;
			else
				which_prog = SWAPON;
			break;
		case 'd':
			if (which_prog == SWAPCTL)
				which_prog = SWAPOFF;
			else
				usage();
			break;
		case 'E':
			if (which_prog == SWAPON)
				Eflag = 2;
			else
				usage();
			break;
		case 'g':
			hflag = 'G';
			break;
		case 'h':
			hflag = 'H';
			break;
		case 'k':
			hflag = 'K';
			break;
		case 'l':
			lflag = 1;
			break;
		case 'L':
			late = 1;
			break;
		case 'm':
			hflag = 'M';
			break;
		case 'q':
			if (which_prog == SWAPON || which_prog == SWAPOFF)
				qflag = 1;
			break;
		case 's':
			sflag = 1;
			break;
		case 'U':
			if (which_prog == SWAPCTL) {
				doall = 1;
				which_prog = SWAPOFF;
			} else
				usage();
			break;
		case 'F':
			etc_fstab = optarg;
			break;
		case '?':
		default:
			usage();
		}
	}
	argv += optind;

	ret = 0;
	swfile = NULL;
	if (etc_fstab != NULL)
		setfstab(etc_fstab);
	if (which_prog == SWAPON || which_prog == SWAPOFF) {
		if (doall) {
			while ((fsp = getfsent()) != NULL) {
				if (strcmp(fsp->fs_type, FSTAB_SW) != 0)
					continue;
				if (strstr(fsp->fs_mntops, "noauto") != NULL)
					continue;
				if (which_prog != SWAPOFF &&
				    strstr(fsp->fs_mntops, "late") &&
				    late == 0)
					continue;
				if (which_prog == SWAPOFF &&
				    strstr(fsp->fs_mntops, "late") == NULL &&
				    late != 0)
					continue;
				Eflag |= (strstr(fsp->fs_mntops, "trimonce") != NULL);
				swfile = swap_on_off(fsp->fs_spec, 1,
				    fsp->fs_mntops);
				Eflag &= ~1;
				if (swfile == NULL) {
					ret = 1;
					continue;
				}
				if (qflag == 0) {
					printf("%s: %sing %s as swap device\n",
					    getprogname(),
					    (which_prog == SWAPOFF) ?
					    "remov" : "add", swfile);
				}
			}
		} else if (*argv == NULL)
			usage();
		for (; *argv; ++argv) {
			swfile = swap_on_off(*argv, 0, NULL);
			if (swfile == NULL) {
				ret = 1;
				continue;
			}
			if (orig_prog == SWAPCTL) {
				printf("%s: %sing %s as swap device\n",
				    getprogname(),
				    (which_prog == SWAPOFF) ? "remov" : "add",
				    swfile);
			}
		}
	} else {
		if (lflag || sflag)
			swaplist(lflag, sflag, hflag);
		else 
			usage();
	}
	exit(ret);
}