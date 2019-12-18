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
struct spectralhandler {int dummy; } ;
typedef  int /*<<< orphan*/  spectral ;

/* Variables and functions */
 char* ATH_DEFAULT ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  memset (struct spectralhandler*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spectral_closedev (struct spectralhandler*) ; 
 int /*<<< orphan*/  spectral_enable_at_reset (struct spectralhandler*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spectral_get (struct spectralhandler*) ; 
 scalar_t__ spectral_opendev (struct spectralhandler*,char const*) ; 
 scalar_t__ spectral_set_param (struct spectralhandler*,char*,char*) ; 
 int /*<<< orphan*/  spectral_start (struct spectralhandler*) ; 
 int /*<<< orphan*/  spectral_stop (struct spectralhandler*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage (char const*) ; 

int
main(int argc, char *argv[])
{
	struct spectralhandler spectral;
	const char *devname = ATH_DEFAULT;
	const char *progname = argv[0];

	memset(&spectral, 0, sizeof(spectral));

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

	if (spectral_opendev(&spectral, devname) == 0)
		exit(127);

	if (strcasecmp(argv[1], "get") == 0) {
		spectral_get(&spectral);
	} else if (strcasecmp(argv[1], "set") == 0) {
		if (argc < 4) {
			usage(progname);
			exit(127);
		}
		if (spectral_set_param(&spectral, argv[2], argv[3]) == 0) {
			usage(progname);
			exit(127);
		}
	} else if (strcasecmp(argv[1], "start") == 0) {
		spectral_start(&spectral);
	} else if (strcasecmp(argv[1], "stop") == 0) {
		spectral_stop(&spectral);
	} else if (strcasecmp(argv[1], "enable_at_reset") == 0) {
		if (argc < 3) {
			usage(progname);
			exit(127);
		}
		spectral_enable_at_reset(&spectral, atoi(argv[2]));
	} else {
		usage(progname);
		exit(127);
	}

	/* wrap up */
	spectral_closedev(&spectral);
	exit(0);
}