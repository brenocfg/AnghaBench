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
 int DEF_BATCH ; 
 int DEF_EXTRA_BUFS ; 
 int DEF_WAIT_LINK ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void usage()
{
	printf("usage: lb [options]\n");
	printf("where options are:\n");
	printf("  -h              	view help text\n");
	printf("  -i iface        	interface name (required)\n");
	printf("  -p [prefix:]npipes	add a new group of output pipes\n");
	printf("  -B nbufs        	number of extra buffers (default: %d)\n", DEF_EXTRA_BUFS);
	printf("  -b batch        	batch size (default: %d)\n", DEF_BATCH);
	printf("  -w seconds        	wait for link up (default: %d)\n", DEF_WAIT_LINK);
	printf("  -W                    enable busy waiting. this will run your CPU at 100%%\n");
	printf("  -s seconds      	seconds between syslog stats messages (default: 0)\n");
	printf("  -o seconds      	seconds between stdout stats messages (default: 0)\n");
	exit(0);
}