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
struct outputter {int dummy; } ;
struct option {char* member_0; float member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  const member_1; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  dump_eltorito (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,struct outputter*) ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int getopt_long (int,char**,char*,struct option*,int /*<<< orphan*/ *) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 struct outputter* output_shell ; 
 struct outputter* output_text ; 
#define  required_argument 128 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage (char*) ; 

int
main(int argc, char **argv)
{
	int ch, i;
	FILE *outfile, *iso;
	struct outputter *outputter;

	outfile = stdout;
	outputter = output_text;

	static struct option longopts[] = {
		{ "format",	required_argument,	NULL,	'f' },
		{ "output",	required_argument,	NULL,	'o' },
		{ NULL,		0,			NULL,	0 },
	};

	while ((ch = getopt_long(argc, argv, "f:o:", longopts, NULL)) != -1) {
		switch (ch) {
		case 'f':
			if (strcmp(optarg, "shell") == 0)
				outputter = output_shell;
			else if (strcmp(optarg, "text") == 0)
				outputter = output_text;
			else
				usage(argv[0]);
			break;
		case 'o':
			if (strcmp(optarg, "-") == 0) {
				outfile = stdout;
			} else if ((outfile = fopen(optarg, "w")) == NULL) {
				err(1, "unable to open %s for output", optarg);
			}
			break;
		default:
			usage(argv[0]);
		}
	}

	argc -= optind;
	argv += optind;

	for (i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-") == 0) {
			iso = stdin;
		} else {
			iso = fopen(argv[i], "r");
			if (iso == NULL)
				err(1, "could not open %s", argv[1]);
		}
		dump_eltorito(iso, argv[i], outfile, outputter);
	}
}