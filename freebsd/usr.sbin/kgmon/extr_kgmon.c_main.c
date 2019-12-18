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
struct kvmvars {int dummy; } ;

/* Variables and functions */
 int Bflag ; 
 int GMON_PROF_BUSY ; 
 int GMON_PROF_ERROR ; 
 int GMON_PROF_HIRES ; 
 int GMON_PROF_OFF ; 
 int GMON_PROF_ON ; 
 int O_RDWR ; 
 int bflag ; 
 int /*<<< orphan*/  dumpstate (struct kvmvars*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* getbootfile () ; 
 int getopt (int,char**,char*) ; 
 int getprof (struct kvmvars*) ; 
 int /*<<< orphan*/  getuid () ; 
 int hflag ; 
 int kflag ; 
 int openfiles (char const*,char*,struct kvmvars*) ; 
 void* optarg ; 
 scalar_t__ optind ; 
 int pflag ; 
 int /*<<< orphan*/  reset (struct kvmvars*) ; 
 int rflag ; 
 scalar_t__ seteuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setprof (struct kvmvars*,int) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	int ch, mode, disp, accessmode;
	struct kvmvars kvmvars;
	const char *systemname;
	char *kmemf;

	if (seteuid(getuid()) != 0) {
		err(1, "seteuid failed\n");
	}
	kmemf = NULL;
	systemname = NULL;
	while ((ch = getopt(argc, argv, "M:N:Bbhpr")) != -1) {
		switch((char)ch) {

		case 'M':
			kmemf = optarg;
			kflag = 1;
			break;

		case 'N':
			systemname = optarg;
			break;

		case 'B':
			Bflag = 1;
			break;

		case 'b':
			bflag = 1;
			break;

		case 'h':
			hflag = 1;
			break;

		case 'p':
			pflag = 1;
			break;

		case 'r':
			rflag = 1;
			break;

		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

#define BACKWARD_COMPATIBILITY
#ifdef	BACKWARD_COMPATIBILITY
	if (*argv) {
		systemname = *argv;
		if (*++argv) {
			kmemf = *argv;
			++kflag;
		}
	}
#endif
	if (systemname == NULL)
		systemname = getbootfile();
	accessmode = openfiles(systemname, kmemf, &kvmvars);
	mode = getprof(&kvmvars);
	if (hflag)
		disp = GMON_PROF_OFF;
	else if (Bflag)
		disp = GMON_PROF_HIRES;
	else if (bflag)
		disp = GMON_PROF_ON;
	else
		disp = mode;
	if (pflag)
		dumpstate(&kvmvars);
	if (rflag)
		reset(&kvmvars);
	if (accessmode == O_RDWR)
		setprof(&kvmvars, disp);
	(void)fprintf(stdout, "kgmon: kernel profiling is %s.\n",
		      disp == GMON_PROF_OFF ? "off" :
		      disp == GMON_PROF_HIRES ? "running (high resolution)" :
		      disp == GMON_PROF_ON ? "running" :
		      disp == GMON_PROF_BUSY ? "busy" :
		      disp == GMON_PROF_ERROR ? "off (error)" :
		      "in an unknown state");
	return (0);
}