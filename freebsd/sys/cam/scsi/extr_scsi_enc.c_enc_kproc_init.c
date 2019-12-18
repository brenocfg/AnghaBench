#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  (* poll_status ) (TYPE_2__*) ;} ;
struct TYPE_12__ {TYPE_6__* periph; TYPE_1__ enc_vec; int /*<<< orphan*/  enc_daemon; int /*<<< orphan*/  status_updater; } ;
typedef  TYPE_2__ enc_softc_t ;
struct TYPE_13__ {int /*<<< orphan*/  unit_number; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cam_periph_acquire (TYPE_6__*) ; 
 int /*<<< orphan*/  cam_periph_lock (TYPE_6__*) ; 
 int /*<<< orphan*/  cam_periph_mtx (TYPE_6__*) ; 
 int /*<<< orphan*/  cam_periph_release (TYPE_6__*) ; 
 int /*<<< orphan*/  cam_periph_unlock (TYPE_6__*) ; 
 int /*<<< orphan*/  enc_daemon ; 
 int kproc_create (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static int
enc_kproc_init(enc_softc_t *enc)
{
	int result;

	callout_init_mtx(&enc->status_updater, cam_periph_mtx(enc->periph), 0);

	if (cam_periph_acquire(enc->periph) != 0)
		return (ENXIO);

	result = kproc_create(enc_daemon, enc, &enc->enc_daemon, /*flags*/0,
			      /*stackpgs*/0, "enc_daemon%d",
			      enc->periph->unit_number);
	if (result == 0) {
		/* Do an initial load of all page data. */
		cam_periph_lock(enc->periph);
		enc->enc_vec.poll_status(enc);
		cam_periph_unlock(enc->periph);
	} else
		cam_periph_release(enc->periph);
	return (result);
}