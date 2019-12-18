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
 int /*<<< orphan*/  EX_USAGE ; 
 char* FMT ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{

#define FMT "    %-14s %s\n"
	fprintf(stderr, "usage: usbdump [options]\n");
	fprintf(stderr, FMT, "-i <usbusX>", "Listen on USB bus interface");
	fprintf(stderr, FMT, "-f <unit[.endpoint]>", "Specify a device and endpoint filter");
	fprintf(stderr, FMT, "-r <file>", "Read the raw packets from file");
	fprintf(stderr, FMT, "-s <snaplen>", "Snapshot bytes from each packet");
	fprintf(stderr, FMT, "-v", "Increase the verbose level");
	fprintf(stderr, FMT, "-b <file>", "Save raw version of all recorded data to file");
	fprintf(stderr, FMT, "-w <file>", "Write the raw packets to file");
	fprintf(stderr, FMT, "-h", "Display summary of command line options");
#undef FMT
	exit(EX_USAGE);
}