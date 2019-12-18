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
 char* CONFIGFILE ; 
 char* PACKAGE_BUGREPORT ; 
 char* PACKAGE_VERSION ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
usage(void)
{
	printf("Usage:	local-unbound-checkconf [file]\n");
	printf("	Checks unbound configuration file for errors.\n");
	printf("file	if omitted %s is used.\n", CONFIGFILE);
	printf("-o option	print value of option to stdout.\n");
	printf("-f 		output full pathname with chroot applied, eg. with -o pidfile.\n");
	printf("-h		show this usage help.\n");
	printf("Version %s\n", PACKAGE_VERSION);
	printf("BSD licensed, see LICENSE in source package for details.\n");
	printf("Report bugs to %s\n", PACKAGE_BUGREPORT);
	exit(1);
}