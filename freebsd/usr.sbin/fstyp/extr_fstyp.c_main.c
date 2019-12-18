#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  strvised ;
typedef  int /*<<< orphan*/  label ;
typedef  int (* fstyp_function ) (int /*<<< orphan*/ *,char*,int) ;
struct TYPE_2__ {int unmountable; int (* function ) (int /*<<< orphan*/ *,char*,int) ;char* name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int LABEL_LEN ; 
 int VIS_GLOB ; 
 int VIS_NL ; 
 scalar_t__ caph_enter () ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 TYPE_1__* fstypes ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int strsnvis (char*,int,char*,int,char*) ; 
 int /*<<< orphan*/  type_check (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int
main(int argc, char **argv)
{
	int ch, error, i, nbytes;
	bool ignore_type = false, show_label = false, show_unmountable = false;
	char label[LABEL_LEN + 1], strvised[LABEL_LEN * 4 + 1];
	char *path;
	FILE *fp;
	fstyp_function fstyp_f;

	while ((ch = getopt(argc, argv, "lsu")) != -1) {
		switch (ch) {
		case 'l':
			show_label = true;
			break;
		case 's':
			ignore_type = true;
			break;
		case 'u':
			show_unmountable = true;
			break;
		default:
			usage();
		}
	}

	argc -= optind;
	argv += optind;
	if (argc != 1)
		usage();

	path = argv[0];

	fp = fopen(path, "r");
	if (fp == NULL)
		err(1, "%s", path);

	if (caph_enter() < 0)
		err(1, "cap_enter");

	if (ignore_type == false)
		type_check(path, fp);

	memset(label, '\0', sizeof(label));

	for (i = 0;; i++) {
		if (show_unmountable == false && fstypes[i].unmountable == true)
			continue;
		fstyp_f = fstypes[i].function;
		if (fstyp_f == NULL)
			break;

		error = fstyp_f(fp, label, sizeof(label));
		if (error == 0)
			break;
	}

	if (fstypes[i].name == NULL) {
		warnx("%s: filesystem not recognized", path);
		return (1);
	}

	if (show_label && label[0] != '\0') {
		/*
		 * XXX: I'd prefer VIS_HTTPSTYLE, but it unconditionally
		 *      encodes spaces.
		 */
		nbytes = strsnvis(strvised, sizeof(strvised), label,
		    VIS_GLOB | VIS_NL, "\"'$");
		if (nbytes == -1)
			err(1, "strsnvis");

		printf("%s %s\n", fstypes[i].name, strvised);
	} else {
		printf("%s\n", fstypes[i].name);
	}

	return (0);
}