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
struct pfilioc_link {int /*<<< orphan*/  pio_ruleset; int /*<<< orphan*/  pio_module; int /*<<< orphan*/  pio_name; scalar_t__ pio_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PFILIOC_LINK ; 
 scalar_t__ PFIL_APPEND ; 
 int /*<<< orphan*/  PFIL_DIR (scalar_t__) ; 
 scalar_t__ PFIL_IN ; 
 scalar_t__ PFIL_OUT ; 
 scalar_t__ PFIL_UNLINK ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  help () ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pfilioc_link*) ; 
 scalar_t__ optind ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
hook(int argc, char *argv[])
{
	struct pfilioc_link req;
	int c;
	char *ruleset;

	if (argv[0][0] == 'u')
		req.pio_flags = PFIL_UNLINK;
	else
		req.pio_flags = 0;

	while ((c = getopt(argc, argv, "ioa")) != -1)
		switch (c) {
		case 'i':
			req.pio_flags |= PFIL_IN;
			break;
		case 'o':
			req.pio_flags |= PFIL_OUT;
			break;
		case 'a':
			req.pio_flags |= PFIL_APPEND;
			break;
		default:
			help();
		}

	if (!PFIL_DIR(req.pio_flags))
		help();

	argc -= optind;
	argv += optind;

	if (argc != 2)
		help();

	/* link mod:ruleset head */
	if ((ruleset = strchr(argv[0], ':')) == NULL)
		help();
	*ruleset = '\0';
	ruleset++;

	strlcpy(req.pio_name, argv[1], sizeof(req.pio_name));
	strlcpy(req.pio_module, argv[0], sizeof(req.pio_module));
	strlcpy(req.pio_ruleset, ruleset, sizeof(req.pio_ruleset));

	if (ioctl(dev, PFILIOC_LINK, &req) != 0)
		err(1, "ioctl(PFILIOC_LINK)");
}