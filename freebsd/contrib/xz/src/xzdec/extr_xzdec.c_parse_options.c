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
struct option {char* member_0; char member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  const member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  display_errors ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt_long (int,char**,char const*,struct option const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  help () ; 
#define  no_argument 128 
 int /*<<< orphan*/  version () ; 

__attribute__((used)) static void
parse_options(int argc, char **argv)
{
	static const char short_opts[] = "cdkM:hqQV";
	static const struct option long_opts[] = {
		{ "stdout",       no_argument,         NULL, 'c' },
		{ "to-stdout",    no_argument,         NULL, 'c' },
		{ "decompress",   no_argument,         NULL, 'd' },
		{ "uncompress",   no_argument,         NULL, 'd' },
		{ "keep",         no_argument,         NULL, 'k' },
		{ "quiet",        no_argument,         NULL, 'q' },
		{ "no-warn",      no_argument,         NULL, 'Q' },
		{ "help",         no_argument,         NULL, 'h' },
		{ "version",      no_argument,         NULL, 'V' },
		{ NULL,           0,                   NULL, 0   }
	};

	int c;

	while ((c = getopt_long(argc, argv, short_opts, long_opts, NULL))
			!= -1) {
		switch (c) {
		case 'c':
		case 'd':
		case 'k':
		case 'Q':
			break;

		case 'q':
			if (display_errors > 0)
				--display_errors;

			break;

		case 'h':
			help();

		case 'V':
			version();

		default:
			exit(EXIT_FAILURE);
		}
	}

	return;
}