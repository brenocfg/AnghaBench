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
typedef  int /*<<< orphan*/  zoneinfo ;
typedef  int /*<<< orphan*/  vm_guest ;
typedef  int /*<<< orphan*/  title ;
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  prompt ;
struct TYPE_2__ {int /*<<< orphan*/  defaultno; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DIALOG_VARS ;

/* Variables and functions */
 int DITEM_LEAVE_MENU ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  NCONTINENTS ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int /*<<< orphan*/  TRUE ; 
 char* _PATH_DB ; 
 char* _PATH_ISO3166 ; 
 char* _PATH_LOCALTIME ; 
 char* _PATH_WALL_CMOS_CLOCK ; 
 char* _PATH_ZONEINFO ; 
 char* _PATH_ZONETAB ; 
 char* chrootenv ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  continents ; 
 TYPE_1__ dialog_vars ; 
 int dialog_yesno (char*,char*,int,int) ; 
 int /*<<< orphan*/  dlg_clear () ; 
 int /*<<< orphan*/  dlg_restore_vars (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlg_save_vars (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  end_dialog () ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  init_dialog (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int install_zoneinfo (char*) ; 
 int install_zoneinfo_file (char*) ; 
 int /*<<< orphan*/  make_menus () ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  path_db ; 
 int /*<<< orphan*/  path_iso3166 ; 
 int /*<<< orphan*/  path_localtime ; 
 int /*<<< orphan*/  path_wall_cmos_clock ; 
 int /*<<< orphan*/  path_zoneinfo ; 
 int /*<<< orphan*/  path_zonetab ; 
 int /*<<< orphan*/  read_iso3166_table () ; 
 int /*<<< orphan*/  read_zones () ; 
 scalar_t__ reallydoit ; 
 int reinstall ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  sort_countries () ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 
 scalar_t__ sysctlbyname (char*,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umask (int) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 scalar_t__ usedialog ; 
 int /*<<< orphan*/  xdialog_menu (char*,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
main(int argc, char **argv)
{
#ifdef HAVE_DIALOG
	char		title[64], prompt[128];
	int		fd;
#endif
	int		c, rv, skiputc;
	char		vm_guest[16] = "";
	size_t		len = sizeof(vm_guest);

	skiputc = 0;

	/* Default skiputc to 1 for VM guests */
	if (sysctlbyname("kern.vm_guest", vm_guest, &len, NULL, 0) == 0 &&
	    strcmp(vm_guest, "none") != 0)
		skiputc = 1;

	while ((c = getopt(argc, argv, "C:nrs")) != -1) {
		switch(c) {
		case 'C':
			chrootenv = optarg;
			break;
		case 'n':
			reallydoit = 0;
			break;
		case 'r':
			reinstall = 1;
#ifdef HAVE_DIALOG
			usedialog = 0;
#endif
			break;
		case 's':
			skiputc = 1;
			break;
		default:
			usage();
		}
	}

	if (argc - optind > 1)
		usage();

	if (chrootenv == NULL) {
		strcpy(path_zonetab, _PATH_ZONETAB);
		strcpy(path_iso3166, _PATH_ISO3166);
		strcpy(path_zoneinfo, _PATH_ZONEINFO);
		strcpy(path_localtime, _PATH_LOCALTIME);
		strcpy(path_db, _PATH_DB);
		strcpy(path_wall_cmos_clock, _PATH_WALL_CMOS_CLOCK);
	} else {
		sprintf(path_zonetab, "%s/%s", chrootenv, _PATH_ZONETAB);
		sprintf(path_iso3166, "%s/%s", chrootenv, _PATH_ISO3166);
		sprintf(path_zoneinfo, "%s/%s", chrootenv, _PATH_ZONEINFO);
		sprintf(path_localtime, "%s/%s", chrootenv, _PATH_LOCALTIME);
		sprintf(path_db, "%s/%s", chrootenv, _PATH_DB);
		sprintf(path_wall_cmos_clock, "%s/%s", chrootenv,
		    _PATH_WALL_CMOS_CLOCK);
	}

	/* Override the user-supplied umask. */
	(void)umask(S_IWGRP | S_IWOTH);

	if (reinstall == 1) {
		FILE *f;
		char zoneinfo[MAXPATHLEN];

		if ((f = fopen(path_db, "r")) != NULL) {
			if (fgets(zoneinfo, sizeof(zoneinfo), f) != NULL) {
				zoneinfo[sizeof(zoneinfo) - 1] = 0;
				if (strlen(zoneinfo) > 0) {
					zoneinfo[strlen(zoneinfo) - 1] = 0;
					rv = install_zoneinfo(zoneinfo);
					exit(rv & ~DITEM_LEAVE_MENU);
				}
				errx(1, "Error reading %s.\n", path_db);
			}
			fclose(f);
			errx(1,
			    "Unable to determine earlier installed zoneinfo "
			    "name. Check %s", path_db);
		}
		errx(1, "Cannot open %s for reading. Does it exist?", path_db);
	}

	/*
	 * If the arguments on the command-line do not specify a file,
	 * then interpret it as a zoneinfo name
	 */
	if (optind == argc - 1) {
		struct stat sb;

		if (stat(argv[optind], &sb) != 0) {
#ifdef HAVE_DIALOG
			usedialog = 0;
#endif
			rv = install_zoneinfo(argv[optind]);
			exit(rv & ~DITEM_LEAVE_MENU);
		}
		/* FALLTHROUGH */
	}
#ifdef HAVE_DIALOG

	read_iso3166_table();
	read_zones();
	sort_countries();
	make_menus();

	init_dialog(stdin, stdout);
	if (skiputc == 0) {
		DIALOG_VARS save_vars;
		int yesno;

		snprintf(title, sizeof(title),
		    "Select local or UTC (Greenwich Mean Time) clock");
		snprintf(prompt, sizeof(prompt),
		    "Is this machine's CMOS clock set to UTC?  "
		    "If it is set to local time,\n"
		    "or you don't know, please choose NO here!");
		dlg_save_vars(&save_vars);
#if !defined(__sparc64__)
		dialog_vars.defaultno = TRUE;
#endif
		yesno = dialog_yesno(title, prompt, 7, 73);
		dlg_restore_vars(&save_vars);
		if (!yesno) {
			if (reallydoit)
				unlink(path_wall_cmos_clock);
		} else {
			if (reallydoit) {
				fd = open(path_wall_cmos_clock,
				    O_WRONLY | O_CREAT | O_TRUNC,
				    S_IRUSR | S_IRGRP | S_IROTH);
				if (fd < 0) {
					end_dialog();
					err(1, "create %s",
					    path_wall_cmos_clock);
				}
				close(fd);
			}
		}
		dlg_clear();
	}
	if (optind == argc - 1) {
		snprintf(title, sizeof(title), "Default timezone provided");
		snprintf(prompt, sizeof(prompt),
		    "\nUse the default `%s' zone?", argv[optind]);
		if (!dialog_yesno(title, prompt, 7, 72)) {
			rv = install_zoneinfo_file(argv[optind]);
			dlg_clear();
			end_dialog();
			exit(rv & ~DITEM_LEAVE_MENU);
		}
		dlg_clear();
	}
	snprintf(title, sizeof(title), "Time Zone Selector");
	snprintf(prompt, sizeof(prompt), "Select a region");
	xdialog_menu(title, prompt, -1, -1, NCONTINENTS, NCONTINENTS,
	    continents);

	dlg_clear();
	end_dialog();
#else
	usage();
#endif
	return (0);
}