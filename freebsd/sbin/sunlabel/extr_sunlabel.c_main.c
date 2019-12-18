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
struct sun_disklabel {int sdkp_nsectors; int sl_ncylinders; int sl_ntracks; int sl_nsectors; scalar_t__ sl_magic; struct sun_disklabel* sl_part; scalar_t__ sdkp_cyloffset; } ;
typedef  int /*<<< orphan*/  sl ;

/* Variables and functions */
 int Bflag ; 
 int Rflag ; 
 scalar_t__ SUN_DKMAGIC ; 
 size_t SUN_RAWPART ; 
 char* _PATH_BOOT ; 
 int /*<<< orphan*/  _PATH_DEV ; 
 int bflag ; 
 int /*<<< orphan*/  bzero (struct sun_disklabel*,int) ; 
 int cflag ; 
 int /*<<< orphan*/  edit_label (struct sun_disklabel*,char const*,char const*) ; 
 int eflag ; 
 int /*<<< orphan*/  errx (int,char*,char const*,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int getopt (int,char**,char*) ; 
 int hflag ; 
 int nflag ; 
 char* optarg ; 
 scalar_t__ optind ; 
 scalar_t__ parse_label (struct sun_disklabel*,char const*) ; 
 int /*<<< orphan*/  print_label (struct sun_disklabel*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_label (struct sun_disklabel*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int wflag ; 
 int /*<<< orphan*/  write_label (struct sun_disklabel*,char const*,char const*) ; 

int
main(int ac, char **av)
{
	struct sun_disklabel sl;
	const char *bootpath;
	const char *proto;
	const char *disk;
	int ch;

	bootpath = _PATH_BOOT; 
	while ((ch = getopt(ac, av, "b:BcehnrRw")) != -1)
		switch (ch) {
		case 'b':
			bflag = 1;
			bootpath = optarg;
			break;
		case 'B':
			Bflag = 1;
			break;
		case 'c':
			cflag = 1;
			break;
		case 'e':
			eflag = 1;
			break;
		case 'h':
			hflag = 1;
			break;
		case 'n':
			nflag = 1;
			break;
		case 'r':
			fprintf(stderr, "Obsolete -r flag ignored\n");
			break;
		case 'R':
			Rflag = 1;
			break;
		case 'w':
			wflag = 1;
			break;
		default:
			usage();
			break;
		}
	if (bflag && !Bflag)
		usage();
	if (nflag && !(Bflag || eflag || Rflag || wflag))
		usage();
	if (eflag && (Rflag || wflag))
		usage();
	if (eflag)
		hflag = 0;
	ac -= optind;
	av += optind;
	if (ac == 0)
		usage();
	bzero(&sl, sizeof(sl));
	disk = av[0];
	if (wflag) {
		if (ac != 2 || strcmp(av[1], "auto") != 0)
			usage();
		read_label(&sl, disk);
		bzero(sl.sl_part, sizeof(sl.sl_part));
		sl.sl_part[SUN_RAWPART].sdkp_cyloffset = 0;
		sl.sl_part[SUN_RAWPART].sdkp_nsectors = sl.sl_ncylinders *
		    sl.sl_ntracks * sl.sl_nsectors;
		write_label(&sl, disk, bootpath);
	} else if (eflag) {
		if (ac != 1)
			usage();
		read_label(&sl, disk);
		if (sl.sl_magic != SUN_DKMAGIC)
			errx(1, "%s%s has no sun disklabel", _PATH_DEV, disk);
		edit_label(&sl, disk, bootpath);
	} else if (Rflag) {
		if (ac != 2)
			usage();
		proto = av[1];
		read_label(&sl, disk);
		if (parse_label(&sl, proto) != 0)
			errx(1, "%s: invalid label", proto);
		write_label(&sl, disk, bootpath);
	} else if (Bflag) {
		read_label(&sl, disk);
		if (sl.sl_magic != SUN_DKMAGIC)
			errx(1, "%s%s has no sun disklabel", _PATH_DEV, disk);
		write_label(&sl, disk, bootpath);
	} else {
		read_label(&sl, disk);
		if (sl.sl_magic != SUN_DKMAGIC)
			errx(1, "%s%s has no sun disklabel", _PATH_DEV, disk);
		print_label(&sl, disk, stdout);
	}
	return (0);
}