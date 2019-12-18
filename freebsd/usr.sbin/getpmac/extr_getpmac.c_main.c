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
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  mac_t ;

/* Variables and functions */
 int EX_DATAERR ; 
 int EX_OK ; 
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  mac_free (int /*<<< orphan*/ ) ; 
 int mac_get_pid (scalar_t__,int /*<<< orphan*/ ) ; 
 int mac_get_proc (int /*<<< orphan*/ ) ; 
 int mac_prepare (int /*<<< orphan*/ *,char*) ; 
 int mac_prepare_process_label (int /*<<< orphan*/ *) ; 
 int mac_to_text (int /*<<< orphan*/ ,char**) ; 
 size_t optind ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	char *labellist, *string;
	mac_t label;
	pid_t pid;
	int ch, error, pid_set;

	pid_set = 0;
	pid = 0;
	labellist = NULL;
	while ((ch = getopt(argc, argv, "l:p:")) != -1) {
		switch (ch) {
		case 'l':
			if (labellist != NULL)
				usage();
			labellist = argv[optind - 1];
			break;
		case 'p':
			if (pid_set)
				usage();
			pid = atoi(argv[optind - 1]);
			pid_set = 1;
			break;
		default:
			usage();
		}

	}

	argc -= optind;
	argv += optind;

	if (argc != 0)
		usage();

	if (labellist != NULL)
		error = mac_prepare(&label, labellist);
	else
		error = mac_prepare_process_label(&label);
	if (error != 0) {
		perror("mac_prepare");
		return (-1);
	}

	if (pid_set) {
		error = mac_get_pid(pid, label);
		if (error)
			perror("mac_get_pid");
	} else {
		error = mac_get_proc(label);
		if (error)
			perror("mac_get_proc");
	}
	if (error) {
		mac_free(label);
		exit (-1);
	}
	error = mac_to_text(label, &string);
	if (error != 0) {
		perror("mac_to_text");
		exit(EX_DATAERR);
	}

	if (strlen(string) > 0)
		printf("%s\n", string);
		
	mac_free(label);
	free(string);
	exit(EX_OK);
}