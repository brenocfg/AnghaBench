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
typedef  int /*<<< orphan*/  mac_t ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OK ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  mac_free (int /*<<< orphan*/ ) ; 
 int mac_get_file (char*,int /*<<< orphan*/ ) ; 
 int mac_get_link (char*,int /*<<< orphan*/ ) ; 
 int mac_prepare (int /*<<< orphan*/ *,char*) ; 
 int mac_prepare_file_label (int /*<<< orphan*/ *) ; 
 int mac_to_text (int /*<<< orphan*/ ,char**) ; 
 int optind ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	char *labellist, *string;
	mac_t label;
	int ch, hflag;
	int error, i;

	labellist = NULL;
	hflag = 0;
	while ((ch = getopt(argc, argv, "hl:")) != -1) {
		switch (ch) {
		case 'h':
			hflag = 1;
			break;
		case 'l':
			if (labellist != NULL)
				usage();
			labellist = argv[optind - 1];
			break;
		default:
			usage();
		}

	}

	for (i = optind; i < argc; i++) {
		if (labellist != NULL)
			error = mac_prepare(&label, labellist);
		else
			error = mac_prepare_file_label(&label);

		if (error != 0) {
			perror("mac_prepare");
			return (-1);
		}

		if (hflag)
			error = mac_get_link(argv[i], label);
		else
			error = mac_get_file(argv[i], label);
		if (error) {
			perror(argv[i]);
			mac_free(label);
			continue;
		}

		error = mac_to_text(label, &string);
		if (error != 0)
			perror("mac_to_text");
		else {
			printf("%s: %s\n", argv[i], string);
			free(string);
		}
		mac_free(label);
	}

	exit(EX_OK);
}