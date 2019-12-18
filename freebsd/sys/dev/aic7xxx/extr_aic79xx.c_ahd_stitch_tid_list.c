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
typedef  int /*<<< orphan*/  u_int ;
struct ahd_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_ASSERT_MODES (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AHD_MODE_SCSI_MSK ; 
 scalar_t__ SCBID_IS_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCB_NEXT2 ; 
 int /*<<< orphan*/  WAITING_TID_HEAD ; 
 int /*<<< orphan*/  WAITING_TID_TAIL ; 
 int /*<<< orphan*/  ahd_outw (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_set_scbptr (struct ahd_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahd_stitch_tid_list(struct ahd_softc *ahd, u_int tid_prev,
		    u_int tid_cur, u_int tid_next)
{
	AHD_ASSERT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);

	if (SCBID_IS_NULL(tid_cur)) {

		/* Bypass current TID list */
		if (SCBID_IS_NULL(tid_prev)) {
			ahd_outw(ahd, WAITING_TID_HEAD, tid_next);
		} else {
			ahd_set_scbptr(ahd, tid_prev);
			ahd_outw(ahd, SCB_NEXT2, tid_next);
		}
		if (SCBID_IS_NULL(tid_next))
			ahd_outw(ahd, WAITING_TID_TAIL, tid_prev);
	} else {

		/* Stitch through tid_cur */
		if (SCBID_IS_NULL(tid_prev)) {
			ahd_outw(ahd, WAITING_TID_HEAD, tid_cur);
		} else {
			ahd_set_scbptr(ahd, tid_prev);
			ahd_outw(ahd, SCB_NEXT2, tid_cur);
		}
		ahd_set_scbptr(ahd, tid_cur);
		ahd_outw(ahd, SCB_NEXT2, tid_next);

		if (SCBID_IS_NULL(tid_next))
			ahd_outw(ahd, WAITING_TID_TAIL, tid_cur);
	}
}