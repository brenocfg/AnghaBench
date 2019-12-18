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
struct bio {int bio_flags; int /*<<< orphan*/  bio_bcount; int /*<<< orphan*/  bio_resid; } ;

/* Variables and functions */
 int BIO_ERROR ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  biodone (struct bio*) ; 
 int /*<<< orphan*/  disk_err (struct bio*,char*,int,int) ; 
 int /*<<< orphan*/  fwprintf (int /*<<< orphan*/ *,char*,char*) ; 

void
aac_biodone(struct bio *bp)
{
	fwprintf(NULL, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	if (bp->bio_flags & BIO_ERROR) {
		bp->bio_resid = bp->bio_bcount;
		disk_err(bp, "hard error", -1, 1);
	}

	biodone(bp);
}