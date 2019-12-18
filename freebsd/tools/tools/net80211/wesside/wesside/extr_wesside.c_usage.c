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
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void usage(char* pname) {
	printf("Usage: %s <opts>\n", pname);
	printf("-h\t\tthis lame message\n");
	printf("-i\t\t<iface>\n");
	printf("-s\t\t<flood server ip>\n");
	printf("-m\t\t<my ip>\n");
	printf("-n\t\t<net ip>\n");
	printf("-r\t\t<rtr mac>\n");
	printf("-a\t\t<mymac>\n");
	printf("-c\t\tdo not crack\n");
	printf("-p\t\t<min prga>\n");
	printf("-4\t\t64 bit key\n");
	printf("-v\t\tvictim mac\n");
	printf("-t\t\t<crack thresh>\n");
	printf("-f\t\t<max chan>\n");
	exit(0);
}