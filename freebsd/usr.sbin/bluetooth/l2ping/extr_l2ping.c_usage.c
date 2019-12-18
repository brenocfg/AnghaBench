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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  NG_L2CAP_MAX_ECHO_SIZE ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	fprintf(stderr, "Usage: l2ping [-fhn] -a remote " \
		"[-c count] [-i wait] [-S source] [-s size]\n");
	fprintf(stderr, "Where:\n");
	fprintf(stderr, "  -a remote  Specify remote device to ping\n");
	fprintf(stderr, "  -c count   Number of packets to send\n");
	fprintf(stderr, "  -f         No delay between packets\n");
	fprintf(stderr, "  -h         Display this message\n");
	fprintf(stderr, "  -i wait    Delay between packets (sec)\n");
	fprintf(stderr, "  -n         Numeric output only\n");
	fprintf(stderr, "  -S source  Specify source device\n");
	fprintf(stderr, "  -s size    Packet size (bytes), " \
		"between %zd and %zd\n", sizeof(int32_t), NG_L2CAP_MAX_ECHO_SIZE);
	
	exit(255);
}