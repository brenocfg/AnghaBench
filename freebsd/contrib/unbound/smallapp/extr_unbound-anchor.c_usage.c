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
 char* P7SIGNER ; 
 char* P7SNAME ; 
 char* PACKAGE_BUGREPORT ; 
 char* PACKAGE_VERSION ; 
 char* ROOT_ANCHOR_FILE ; 
 char* ROOT_CERT_FILE ; 
 char* URLNAME ; 
 char* XMLNAME ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
usage(void)
{
	printf("Usage:	local-unbound-anchor [opts]\n");
	printf("	Setup or update root anchor. "
		"Most options have defaults.\n");
	printf("	Run this program before you start the validator.\n");
	printf("\n");
	printf("	The anchor and cert have default builtin content\n");
	printf("	if the file does not exist or is empty.\n");
	printf("\n");
	printf("-a file		root key file, default %s\n", ROOT_ANCHOR_FILE);
	printf("		The key is input and output for this tool.\n");
	printf("-c file		cert file, default %s\n", ROOT_CERT_FILE);
	printf("-l		list builtin key and cert on stdout\n");
	printf("-u name		server in https url, default %s\n", URLNAME);
	printf("-x path		pathname to xml in url, default %s\n", XMLNAME);
	printf("-s path		pathname to p7s in url, default %s\n", P7SNAME);
	printf("-n name		signer's subject emailAddress, default %s\n", P7SIGNER);
	printf("-4		work using IPv4 only\n");
	printf("-6		work using IPv6 only\n");
	printf("-f resolv.conf	use given resolv.conf\n");
	printf("-r root.hints	use given root.hints\n"
		"		builtin root hints are used by default\n");
	printf("-R		fallback from -f to root query on error\n");
	printf("-v		more verbose\n");
	printf("-C conf		debug, read config\n");
	printf("-P port		use port for https connect, default 443\n");
	printf("-F 		debug, force update with cert\n");
	printf("-h		show this usage help\n");
	printf("Version %s\n", PACKAGE_VERSION);
	printf("BSD licensed, see LICENSE in source package for details.\n");
	printf("Report bugs to %s\n", PACKAGE_BUGREPORT);
	exit(1);
}