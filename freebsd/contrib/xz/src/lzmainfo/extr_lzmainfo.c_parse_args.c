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
struct option {char* member_0; int member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  const member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt_long (int,char**,char*,struct option const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  help () ; 
#define  no_argument 128 
 int /*<<< orphan*/  version () ; 

__attribute__((used)) static void
parse_args(int argc, char **argv)
{
	enum {
		OPT_HELP,
		OPT_VERSION,
	};

	static const struct option long_opts[] = {
		{ "help",    no_argument, NULL, OPT_HELP },
		{ "version", no_argument, NULL, OPT_VERSION },
		{ NULL,      0,           NULL, 0 }
	};

	int c;
	while ((c = getopt_long(argc, argv, "", long_opts, NULL)) != -1) {
		switch (c) {
		case OPT_HELP:
			help();

		case OPT_VERSION:
			version();

		default:
			exit(EXIT_FAILURE);
		}
	}

	return;
}