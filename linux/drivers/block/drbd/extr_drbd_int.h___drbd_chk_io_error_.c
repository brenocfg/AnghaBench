#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  disk; } ;
struct drbd_device {TYPE_2__ state; int /*<<< orphan*/  flags; TYPE_1__* ldev; } ;
typedef  enum drbd_io_error_p { ____Placeholder_drbd_io_error_p } drbd_io_error_p ;
typedef  enum drbd_force_detach_flags { ____Placeholder_drbd_force_detach_flags } drbd_force_detach_flags ;
struct TYPE_6__ {int on_io_error; } ;
struct TYPE_4__ {int /*<<< orphan*/  disk_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_HARD ; 
 int DRBD_FORCE_DETACH ; 
 int DRBD_READ_ERROR ; 
 int DRBD_WRITE_ERROR ; 
 int /*<<< orphan*/  D_FAILED ; 
 int /*<<< orphan*/  D_INCONSISTENT ; 
#define  EP_CALL_HELPER 130 
#define  EP_DETACH 129 
#define  EP_PASS_ON 128 
 int /*<<< orphan*/  FORCE_DETACH ; 
 int /*<<< orphan*/  WAS_IO_ERROR ; 
 int /*<<< orphan*/  WAS_READ_ERROR ; 
 int /*<<< orphan*/  _NS (struct drbd_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ratelimit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _drbd_set_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disk ; 
 int /*<<< orphan*/  drbd_err (struct drbd_device*,char*,char const*) ; 
 int /*<<< orphan*/  drbd_ratelimit_state ; 
 TYPE_3__* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void __drbd_chk_io_error_(struct drbd_device *device,
		enum drbd_force_detach_flags df,
		const char *where)
{
	enum drbd_io_error_p ep;

	rcu_read_lock();
	ep = rcu_dereference(device->ldev->disk_conf)->on_io_error;
	rcu_read_unlock();
	switch (ep) {
	case EP_PASS_ON: /* FIXME would this be better named "Ignore"? */
		if (df == DRBD_READ_ERROR || df == DRBD_WRITE_ERROR) {
			if (__ratelimit(&drbd_ratelimit_state))
				drbd_err(device, "Local IO failed in %s.\n", where);
			if (device->state.disk > D_INCONSISTENT)
				_drbd_set_state(_NS(device, disk, D_INCONSISTENT), CS_HARD, NULL);
			break;
		}
		/* fall through - for DRBD_META_IO_ERROR or DRBD_FORCE_DETACH */
	case EP_DETACH:
	case EP_CALL_HELPER:
		/* Remember whether we saw a READ or WRITE error.
		 *
		 * Recovery of the affected area for WRITE failure is covered
		 * by the activity log.
		 * READ errors may fall outside that area though. Certain READ
		 * errors can be "healed" by writing good data to the affected
		 * blocks, which triggers block re-allocation in lower layers.
		 *
		 * If we can not write the bitmap after a READ error,
		 * we may need to trigger a full sync (see w_go_diskless()).
		 *
		 * Force-detach is not really an IO error, but rather a
		 * desperate measure to try to deal with a completely
		 * unresponsive lower level IO stack.
		 * Still it should be treated as a WRITE error.
		 *
		 * Meta IO error is always WRITE error:
		 * we read meta data only once during attach,
		 * which will fail in case of errors.
		 */
		set_bit(WAS_IO_ERROR, &device->flags);
		if (df == DRBD_READ_ERROR)
			set_bit(WAS_READ_ERROR, &device->flags);
		if (df == DRBD_FORCE_DETACH)
			set_bit(FORCE_DETACH, &device->flags);
		if (device->state.disk > D_FAILED) {
			_drbd_set_state(_NS(device, disk, D_FAILED), CS_HARD, NULL);
			drbd_err(device,
				"Local IO failed in %s. Detaching...\n", where);
		}
		break;
	}
}