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
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  hostmode (char*,int) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  protomode (char*,int) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	int	opt, brief = 0, proto = 0;

	while ((opt = getopt(argc, argv, "bhp")) != -1) {
		switch (opt) {
		case 'b':
			brief = 1;
			break;

		case 'p':
			proto = 1;
			break;

		case 'h':
		default:
			usage();
			/* NOT REACHED */
		}
	}

	argc -= optind;
	argv += optind;

	if (argc < 1)
		usage();

	exit(proto? protomode(*argv, brief) : hostmode(*argv, brief));
}