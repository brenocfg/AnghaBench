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

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int hostapd_main (int,char**) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strstr (char*,char*) ; 
 int wpa_supplicant_main (int,char**) ; 

int main(int argc, char **argv)
{
	bool restart = false;
	const char *prog = argv[0];

restart:
	if (strstr(argv[0], "hostapd"))
		return hostapd_main(argc, argv);
	else if (strstr(argv[0], "wpa_supplicant"))
		return wpa_supplicant_main(argc, argv);

	if (!restart && argc > 1) {
		argv++;
		argc--;
		restart = true;
		goto restart;
	}

	fprintf(stderr, "Invalid command.\nUsage: %s wpa_supplicant|hostapd [<arguments>]\n", prog);
	return 255;
}