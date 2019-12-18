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
struct nfsd_pnfsd_args {char* dspath; int /*<<< orphan*/  op; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSSVC_PNFSDS ; 
 int /*<<< orphan*/  PNFSDOP_DELDSSERVER ; 
 int /*<<< orphan*/  PNFSDOP_FORCEDELDS ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ geteuid () ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  longopts ; 
 scalar_t__ nfssvc (int /*<<< orphan*/ ,struct nfsd_pnfsd_args*) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	struct nfsd_pnfsd_args pnfsdarg;
	int ch, force;

	if (geteuid() != 0)
		errx(1, "Must be run as root/su");
	force = 0;
	while ((ch = getopt_long(argc, argv, "f", longopts, NULL)) != -1) {
		switch (ch) {
		case 'f':
			force = 1;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;
	if (argc != 1)
		usage();

	if (force != 0)
		pnfsdarg.op = PNFSDOP_FORCEDELDS;
	else
		pnfsdarg.op = PNFSDOP_DELDSSERVER;
	pnfsdarg.dspath = *argv;
	if (nfssvc(NFSSVC_PNFSDS, &pnfsdarg) < 0)
		err(1, "Can't kill %s", *argv);
}