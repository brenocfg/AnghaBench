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
struct lcd_driver {int /*<<< orphan*/  l_finish; int /*<<< orphan*/  (* l_prepare ) (char*,char*) ;int /*<<< orphan*/  l_name; int /*<<< orphan*/ * l_code; } ;

/* Variables and functions */
 char* DEFAULT_DEVICE ; 
 int EOF ; 
 int /*<<< orphan*/  EX_OK ; 
 int /*<<< orphan*/  _IONBF ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug (int,char*,...) ; 
 int /*<<< orphan*/  debuglevel ; 
 int /*<<< orphan*/  do_char (struct lcd_driver*,char) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fgetc (int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 int getopt (int,char**,char*) ; 
 struct lcd_driver* lcd_drivertab ; 
 char* progname ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ *) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  stub1 (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int vflag ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int
main(int argc, char *argv[]) 
{
    extern char		*optarg;
    extern int		optind;
    struct lcd_driver	*driver = &lcd_drivertab[0];
    char		*drivertype, *cp;
    char		*devname = DEFAULT_DEVICE;
    char		*drvopts = NULL;
    int			ch, i;

    if ((progname = strrchr(argv[0], '/'))) {
	progname++;
    } else {
	progname = argv[0];
    }

    drivertype = getenv("LCD_TYPE");
    
    while ((ch = getopt(argc, argv, "Dd:f:o:v")) != -1) {
	switch(ch) {
	case 'D':
	    debuglevel++;
	    break;
	case 'd':
	    drivertype = optarg;
	    break;
	case 'f':
	    devname = optarg;
	    break;
	case 'o':
	    drvopts = optarg;
	    break;
	case 'v':
	    vflag = 1;
	    break;
	default:
	    usage();
	}
    }
    argc -= optind;
    argv += optind;
    
    /* If an LCD type was specified, look it up */
    if (drivertype != NULL) {
	driver = NULL;
	for (i = 0; lcd_drivertab[i].l_code != NULL; i++) {
	    if (!strcmp(drivertype, lcd_drivertab[i].l_code)) {
		driver = &lcd_drivertab[i];
		break;
	    }
	}
	if (driver == NULL) {
	    warnx("LCD driver '%s' not known", drivertype);
	    usage();
	}
    }
    debug(1, "Driver selected for %s", driver->l_name);
    driver->l_prepare(devname, drvopts);
    atexit(driver->l_finish);

    if (argc > 0) {
	debug(2, "reading input from %d argument%s", argc, (argc > 1) ? "s" : "");
	for (i = 0; i < argc; i++)
	    for (cp = argv[i]; *cp; cp++)
		do_char(driver, *cp);
    } else {
	debug(2, "reading input from stdin");
	setvbuf(stdin, NULL, _IONBF, 0);
	while ((ch = fgetc(stdin)) != EOF)
	    do_char(driver, (char)ch);
    }
    exit(EX_OK);
}