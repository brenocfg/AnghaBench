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
typedef  int /*<<< orphan*/  kvm_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int _POSIX2_LINE_MAX ; 
 int /*<<< orphan*/  ddb_capture_print_kvm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddb_capture_print_sysctl () ; 
 int /*<<< orphan*/  ddb_capture_status_kvm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddb_capture_status_sysctl () ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ kvm_nlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kvm_openfiles (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  namelist ; 
 char* optarg ; 
 scalar_t__ optind ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 

void
ddb_capture(int argc, char *argv[])
{
	char *mflag, *nflag, errbuf[_POSIX2_LINE_MAX];
	kvm_t *kvm;
	int ch;

	mflag = NULL;
	nflag = NULL;
	kvm = NULL;
	while ((ch = getopt(argc, argv, "M:N:")) != -1) {
		switch (ch) {
		case 'M':
			mflag = optarg;
			break;

		case 'N':
			nflag = optarg;
			break;

		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (argc != 1)
		usage();

	if (mflag != NULL) {
		kvm = kvm_openfiles(nflag, mflag, NULL, O_RDONLY, errbuf);
		if (kvm == NULL)
			errx(-1, "ddb_capture: kvm_openfiles: %s", errbuf);
		if (kvm_nlist(kvm, namelist) != 0)
			errx(-1, "ddb_capture: kvm_nlist");
	} else if (nflag != NULL)
		usage();
	if (strcmp(argv[0], "print") == 0) {
		if (kvm != NULL)
			ddb_capture_print_kvm(kvm);
		else
			ddb_capture_print_sysctl();
	} else if (strcmp(argv[0], "status") == 0) {
		if (kvm != NULL)
			ddb_capture_status_kvm(kvm);
		else
			ddb_capture_status_sysctl();
	} else
		usage();
}