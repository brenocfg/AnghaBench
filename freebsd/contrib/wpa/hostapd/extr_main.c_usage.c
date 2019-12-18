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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  show_version () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void usage(void)
{
	show_version();
	fprintf(stderr,
		"\n"
		"usage: hostapd [-hdBKtv] [-P <PID file>] [-e <entropy file>] "
		"\\\n"
		"         [-g <global ctrl_iface>] [-G <group>]\\\n"
		"         [-i <comma-separated list of interface names>]\\\n"
		"         <configuration file(s)>\n"
		"\n"
		"options:\n"
		"   -h   show this usage\n"
		"   -d   show more debug messages (-dd for even more)\n"
		"   -B   run daemon in the background\n"
		"   -e   entropy file\n"
		"   -g   global control interface path\n"
		"   -G   group for control interfaces\n"
		"   -P   PID file\n"
		"   -K   include key data in debug messages\n"
#ifdef CONFIG_DEBUG_FILE
		"   -f   log output to debug file instead of stdout\n"
#endif /* CONFIG_DEBUG_FILE */
#ifdef CONFIG_DEBUG_LINUX_TRACING
		"   -T   record to Linux tracing in addition to logging\n"
		"        (records all messages regardless of debug verbosity)\n"
#endif /* CONFIG_DEBUG_LINUX_TRACING */
		"   -i   list of interface names to use\n"
#ifdef CONFIG_DEBUG_SYSLOG
		"   -s   log output to syslog instead of stdout\n"
#endif /* CONFIG_DEBUG_SYSLOG */
		"   -S   start all the interfaces synchronously\n"
		"   -t   include timestamps in some debug messages\n"
		"   -v   show hostapd version\n");

	exit(1);
}