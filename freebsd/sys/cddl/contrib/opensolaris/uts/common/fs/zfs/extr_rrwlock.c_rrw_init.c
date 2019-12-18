#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  rr_track_all; int /*<<< orphan*/  rr_writer_wanted; int /*<<< orphan*/  rr_linked_rcount; int /*<<< orphan*/  rr_anon_rcount; int /*<<< orphan*/ * rr_writer; int /*<<< orphan*/  rr_cv; int /*<<< orphan*/  rr_lock; } ;
typedef  TYPE_1__ rrwlock_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  CV_DEFAULT ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_refcount_create (int /*<<< orphan*/ *) ; 

void
rrw_init(rrwlock_t *rrl, boolean_t track_all)
{
	mutex_init(&rrl->rr_lock, NULL, MUTEX_DEFAULT, NULL);
	cv_init(&rrl->rr_cv, NULL, CV_DEFAULT, NULL);
	rrl->rr_writer = NULL;
	zfs_refcount_create(&rrl->rr_anon_rcount);
	zfs_refcount_create(&rrl->rr_linked_rcount);
	rrl->rr_writer_wanted = B_FALSE;
	rrl->rr_track_all = track_all;
}