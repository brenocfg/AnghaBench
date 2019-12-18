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
typedef  int u_int32_t ;
struct dos_partition {scalar_t__ dp_typ; int dp_start; scalar_t__ dp_size; int dp_shd; int dp_ehd; void* dp_esect; void* dp_ecyl; void* dp_ssect; void* dp_scyl; } ;

/* Variables and functions */
 void* DOSCYL (int) ; 
 void* DOSSECT (int,int) ; 
 int dos_cylsecs ; 
 int dos_sectors ; 
 int /*<<< orphan*/  memcpy (struct dos_partition*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtpart ; 

__attribute__((used)) static void
dos(struct dos_partition *partp)
{
	int cy, sec;
	u_int32_t end;

	if (partp->dp_typ == 0 && partp->dp_start == 0 && partp->dp_size == 0) {
		memcpy(partp, &mtpart, sizeof(*partp));
		return;
	}

	/* Start c/h/s. */
	partp->dp_shd = partp->dp_start % dos_cylsecs / dos_sectors;
	cy = partp->dp_start / dos_cylsecs;
	sec = partp->dp_start % dos_sectors + 1;
	partp->dp_scyl = DOSCYL(cy);
	partp->dp_ssect = DOSSECT(sec, cy);

	/* End c/h/s. */
	end = partp->dp_start + partp->dp_size - 1;
	partp->dp_ehd = end % dos_cylsecs / dos_sectors;
	cy = end / dos_cylsecs;
	sec = end % dos_sectors + 1;
	partp->dp_ecyl = DOSCYL(cy);
	partp->dp_esect = DOSSECT(sec, cy);
}