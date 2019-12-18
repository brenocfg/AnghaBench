#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {scalar_t__ b_spa; } ;
typedef  TYPE_1__ arc_buf_hdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCSTAT_BUMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ HDR_HAS_L2HDR (TYPE_1__*) ; 
 scalar_t__ HDR_IO_IN_PROGRESS (TYPE_1__*) ; 
 int /*<<< orphan*/  HDR_L2CACHE (TYPE_1__*) ; 
 int /*<<< orphan*/  arcstat_l2_write_hdr_io_in_progress ; 
 int /*<<< orphan*/  arcstat_l2_write_in_l2 ; 
 int /*<<< orphan*/  arcstat_l2_write_not_cacheable ; 
 int /*<<< orphan*/  arcstat_l2_write_spa_mismatch ; 

__attribute__((used)) static boolean_t
l2arc_write_eligible(uint64_t spa_guid, arc_buf_hdr_t *hdr)
{
	/*
	 * A buffer is *not* eligible for the L2ARC if it:
	 * 1. belongs to a different spa.
	 * 2. is already cached on the L2ARC.
	 * 3. has an I/O in progress (it may be an incomplete read).
	 * 4. is flagged not eligible (zfs property).
	 */
	if (hdr->b_spa != spa_guid) {
		ARCSTAT_BUMP(arcstat_l2_write_spa_mismatch);
		return (B_FALSE);
	}
	if (HDR_HAS_L2HDR(hdr)) {
		ARCSTAT_BUMP(arcstat_l2_write_in_l2);
		return (B_FALSE);
	}
	if (HDR_IO_IN_PROGRESS(hdr)) {
		ARCSTAT_BUMP(arcstat_l2_write_hdr_io_in_progress);
		return (B_FALSE);
	}
	if (!HDR_L2CACHE(hdr)) {
		ARCSTAT_BUMP(arcstat_l2_write_not_cacheable);
		return (B_FALSE);
	}

	return (B_TRUE);
}