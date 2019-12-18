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
struct radarhandler {int dummy; } ;
typedef  int /*<<< orphan*/  radar ;

/* Variables and functions */
 char* ATH_DEFAULT ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  memset (struct radarhandler*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radar_closedev (struct radarhandler*) ; 
 int /*<<< orphan*/  radar_get (struct radarhandler*) ; 
 scalar_t__ radar_opendev (struct radarhandler*,char const*) ; 
 scalar_t__ radar_set_param (struct radarhandler*,char*,char*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage (char const*) ; 

int
main(int argc, char *argv[])
{
	struct radarhandler radar;
	const char *devname = ATH_DEFAULT;
	const char *progname = argv[0];

	memset(&radar, 0, sizeof(radar));

	/* Parse command line options */
	if (argc >= 2 && strcmp(argv[1], "-h") == 0) {
		usage(progname);
		exit(0);
	}
	if (argc >= 2 && strcmp(argv[1], "-?") == 0) {
		usage(progname);
		exit(0);
	}

	if (argc >= 2 && strcmp(argv[1], "-i") == 0) {
		if (argc == 2) {
			usage(progname);
			exit(127);
		}
		devname = argv[2];
		argc -= 2; argv += 2;
	}

	/* At this point we require at least one command */
	if (argc == 1) {
		usage(progname);
		exit(127);
	}

	if (radar_opendev(&radar, devname) == 0)
		exit(127);

	if (strcasecmp(argv[1], "get") == 0) {
		radar_get(&radar);
	} else if (strcasecmp(argv[1], "set") == 0) {
		if (argc < 4) {
			usage(progname);
			exit(127);
		}
		if (radar_set_param(&radar, argv[2], argv[3]) == 0) {
			usage(progname);
			exit(127);
		}
	} else {
		usage(progname);
		exit(127);
	}

	/* wrap up */
	radar_closedev(&radar);
	exit(0);
}