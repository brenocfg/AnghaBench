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
 char* PACKAGE_BUGREPORT ; 
 char* PACKAGE_VERSION ; 
 char* ROOT_ANCHOR_FILE ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
usage(void)
{
	printf("Usage:	unbound-host [-C configfile] [-vdhr46] [-c class] [-t type]\n");
	printf("                     [-y key] [-f keyfile] [-F namedkeyfile] hostname\n");
	printf("  Queries the DNS for information.\n");
	printf("  The hostname is looked up for IP4, IP6 and mail.\n");
	printf("  If an ip-address is given a reverse lookup is done.\n");
	printf("  Use the -v option to see DNSSEC security information.\n");
	printf("    -t type		what type to look for.\n");
	printf("    -c class		what class to look for, if not class IN.\n");
	printf("    -y 'keystring'	specify trust anchor, DS or DNSKEY, like\n");
	printf("			-y 'example.com DS 31560 5 1 1CFED8478...'\n");
	printf("    -D			DNSSEC enable with default root anchor\n");
	printf("    			from %s\n", ROOT_ANCHOR_FILE);
	printf("    -f keyfile		read trust anchors from file, with lines as -y.\n");
	printf("    -F keyfile		read named.conf-style trust anchors.\n");
	printf("    -C config		use the specified unbound.conf (none read by default)\n");
	printf("			pass as first argument if you want to override some\n");
	printf("			options with further arguments\n");
	printf("    -r			read forwarder information from /etc/resolv.conf\n");
	printf("      			breaks validation if the forwarder does not do DNSSEC.\n");
	printf("    -v			be more verbose, shows nodata and security.\n");
	printf("    -d			debug, traces the action, -d -d shows more.\n");
	printf("    -4			use ipv4 network, avoid ipv6.\n");
	printf("    -6			use ipv6 network, avoid ipv4.\n");
	printf("    -h			show this usage help.\n");
	printf("Version %s\n", PACKAGE_VERSION);
	printf("BSD licensed, see LICENSE in source package for details.\n");
	printf("Report bugs to %s\n", PACKAGE_BUGREPORT);
	exit(1);
}