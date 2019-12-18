#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct sun_disklabel {scalar_t__ sl_vtoc_sane; int sl_ncylinders; int sl_ntracks; int sl_nsectors; TYPE_2__* sl_part; TYPE_1__* sl_vtoc_map; } ;
struct TYPE_4__ {scalar_t__ sdkp_cyloffset; int sdkp_nsectors; } ;
struct TYPE_3__ {scalar_t__ svtoc_tag; int svtoc_flag; } ;

/* Variables and functions */
 int SUN_NPART ; 
 size_t SUN_RAWPART ; 
 scalar_t__ SUN_VTOC_SANE ; 
 scalar_t__ VTOC_BACKUP ; 
 int VTOC_UNMNT ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
check_label(struct sun_disklabel *sl)
{
	uint64_t nsectors;
	uint64_t ostart;
	uint64_t start;
	uint64_t oend;
	uint64_t end;
	int havevtoc;
	int warnonly;
	int i;
	int j;

	havevtoc = sl->sl_vtoc_sane == SUN_VTOC_SANE;

	nsectors = sl->sl_ncylinders * sl->sl_ntracks * sl->sl_nsectors;
	if (sl->sl_part[SUN_RAWPART].sdkp_cyloffset != 0 ||
	    sl->sl_part[SUN_RAWPART].sdkp_nsectors != nsectors) {
		warnx("partition c is incorrect, must start at 0 and cover "
		    "whole disk");
		return (1);
	}
	if (havevtoc && sl->sl_vtoc_map[2].svtoc_tag != VTOC_BACKUP) {
		warnx("partition c must have tag \"backup\"");
		return (1);
	}
	for (i = 0; i < SUN_NPART; i++) {
		if (i == 2 || sl->sl_part[i].sdkp_nsectors == 0)
			continue;
		start = (uint64_t)sl->sl_part[i].sdkp_cyloffset *
		    sl->sl_ntracks * sl->sl_nsectors;
		end = start + sl->sl_part[i].sdkp_nsectors;
		if (end > nsectors) {
			warnx("partition %c extends past end of disk",
			    'a' + i);
			return (1);
		}
		if (havevtoc) {
			if (sl->sl_vtoc_map[i].svtoc_tag == VTOC_BACKUP) {
				warnx("only partition c is allowed to have "
				    "tag \"backup\"");
				return (1);
			}
		}
		for (j = 0; j < SUN_NPART; j++) {
			/* 
			 * Overlaps for unmountable partitions are
			 * non-fatal but will be warned anyway.
			 */
			warnonly = havevtoc &&
				((sl->sl_vtoc_map[i].svtoc_flag & VTOC_UNMNT) != 0 ||
				 (sl->sl_vtoc_map[j].svtoc_flag & VTOC_UNMNT) != 0);

			if (j == 2 || j == i ||
			    sl->sl_part[j].sdkp_nsectors == 0)
				continue;
			ostart = (uint64_t)sl->sl_part[j].sdkp_cyloffset *
			    sl->sl_ntracks * sl->sl_nsectors;
			oend = ostart + sl->sl_part[j].sdkp_nsectors;
			if ((start <= ostart && end >= oend) ||
			    (start > ostart && start < oend) ||
			    (end > ostart && end < oend)) {
				warnx("partition %c overlaps partition %c",
				    'a' + i, 'a' + j);
				if (!warnonly)
					return (1);
			}
		}
	}
	return (0);
}