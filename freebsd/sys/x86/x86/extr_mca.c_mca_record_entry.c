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
struct mca_record {int dummy; } ;
struct mca_internal {struct mca_record rec; } ;
typedef  enum scan_mode { ____Placeholder_scan_mode } scan_mode ;

/* Variables and functions */
 int /*<<< orphan*/  M_MCA ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int POLLED ; 
 struct mca_internal* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct mca_internal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 struct mca_internal* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mca_freecount ; 
 int /*<<< orphan*/  mca_freelist ; 
 int /*<<< orphan*/  mca_lock ; 
 int /*<<< orphan*/  mca_log (struct mca_record const*) ; 
 int /*<<< orphan*/  mca_pending ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
mca_record_entry(enum scan_mode mode, const struct mca_record *record)
{
	struct mca_internal *rec;

	if (mode == POLLED) {
		rec = malloc(sizeof(*rec), M_MCA, M_WAITOK);
		mtx_lock_spin(&mca_lock);
	} else {
		mtx_lock_spin(&mca_lock);
		rec = STAILQ_FIRST(&mca_freelist);
		if (rec == NULL) {
			printf("MCA: Unable to allocate space for an event.\n");
			mca_log(record);
			mtx_unlock_spin(&mca_lock);
			return;
		}
		STAILQ_REMOVE_HEAD(&mca_freelist, link);
		mca_freecount--;
	}

	rec->rec = *record;
	STAILQ_INSERT_TAIL(&mca_pending, rec, link);
	mtx_unlock_spin(&mca_lock);
}