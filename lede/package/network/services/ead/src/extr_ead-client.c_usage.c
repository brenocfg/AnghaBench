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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
usage(const char *prog)
{
	fprintf(stderr, "Usage: %s [-s <addr>] [-b <addr>] <node> <username>[:<password>] <command>\n"
		"\n"
		"\t-s <addr>:  Set the server's source address to <addr>\n"
		"\t-b <addr>:  Set the broadcast address to <addr>\n"
		"\t<node>:     Node ID (4 digits hex)\n"
		"\t<username>: Username to authenticate with\n"
		"\n"
		"\tPassing no arguments shows a list of active nodes on the network\n"
		"\n", prog);
	return -1;
}