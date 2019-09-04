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
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  pack (int,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  unpack () ; 
 int /*<<< orphan*/  unpack_sideband () ; 

int cmd__pkt_line(int argc, const char **argv)
{
	if (argc < 2)
		die("too few arguments");

	if (!strcmp(argv[1], "pack"))
		pack(argc - 2, argv + 2);
	else if (!strcmp(argv[1], "unpack"))
		unpack();
	else if (!strcmp(argv[1], "unpack-sideband"))
		unpack_sideband();
	else
		die("invalid argument '%s'", argv[1]);

	return 0;
}