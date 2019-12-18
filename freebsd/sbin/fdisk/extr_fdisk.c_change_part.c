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
struct dos_partition {int dp_typ; int dp_start; int dp_size; int dp_shd; int dp_ehd; void* dp_esect; void* dp_ecyl; void* dp_ssect; void* dp_scyl; } ;
struct TYPE_2__ {struct dos_partition* parts; } ;

/* Variables and functions */
 void* DOSCYL (int) ; 
 void* DOSSECT (int,int) ; 
 int DPCYL (void*,void*) ; 
 int DPSECT (void*) ; 
 int /*<<< orphan*/  Decimal (char*,int,int,int) ; 
 int NO_DISK_SECTORS ; 
 int NO_TRACK_CYLINDERS ; 
 int NO_TRACK_HEADS ; 
 int NO_TRACK_SECTORS ; 
 int /*<<< orphan*/  bzero (struct dos_partition*,int) ; 
 int /*<<< orphan*/  dos (struct dos_partition*) ; 
 scalar_t__ i_flag ; 
 int /*<<< orphan*/  init_sector0 (int) ; 
 TYPE_1__ mboot ; 
 scalar_t__ ok (char*) ; 
 int /*<<< orphan*/  print_part (struct dos_partition*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sanitize_partition (struct dos_partition*) ; 
 scalar_t__ u_flag ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
change_part(int i)
{
    struct dos_partition *partp = &mboot.parts[i - 1];

    printf("The data for partition %d is:\n", i);
    print_part(partp);

    if (u_flag && ok("Do you want to change it?")) {
	int tmp;

	if (i_flag) {
	    bzero(partp, sizeof (*partp));
	    if (i == 1) {
		init_sector0(1);
		printf("\nThe static data for the slice 1 has been reinitialized to:\n");
		print_part(partp);
	    }
	}

	do {
		Decimal("sysid (165=FreeBSD)", partp->dp_typ, tmp, 255);
		Decimal("start", partp->dp_start, tmp, NO_DISK_SECTORS);
		Decimal("size", partp->dp_size, tmp, NO_DISK_SECTORS);
		if (!sanitize_partition(partp)) {
			warnx("ERROR: failed to adjust; setting sysid to 0");
			partp->dp_typ = 0;
		}

		if (ok("Explicitly specify beg/end address ?"))
		{
			int	tsec,tcyl,thd;
			tcyl = DPCYL(partp->dp_scyl,partp->dp_ssect);
			thd = partp->dp_shd;
			tsec = DPSECT(partp->dp_ssect);
			Decimal("beginning cylinder", tcyl, tmp, NO_TRACK_CYLINDERS);
			Decimal("beginning head", thd, tmp, NO_TRACK_HEADS);
			Decimal("beginning sector", tsec, tmp, NO_TRACK_SECTORS);
			partp->dp_scyl = DOSCYL(tcyl);
			partp->dp_ssect = DOSSECT(tsec,tcyl);
			partp->dp_shd = thd;

			tcyl = DPCYL(partp->dp_ecyl,partp->dp_esect);
			thd = partp->dp_ehd;
			tsec = DPSECT(partp->dp_esect);
			Decimal("ending cylinder", tcyl, tmp, NO_TRACK_CYLINDERS);
			Decimal("ending head", thd, tmp, NO_TRACK_HEADS);
			Decimal("ending sector", tsec, tmp, NO_TRACK_SECTORS);
			partp->dp_ecyl = DOSCYL(tcyl);
			partp->dp_esect = DOSSECT(tsec,tcyl);
			partp->dp_ehd = thd;
		} else
			dos(partp);

		print_part(partp);
	} while (!ok("Are we happy with this entry?"));
    }
}