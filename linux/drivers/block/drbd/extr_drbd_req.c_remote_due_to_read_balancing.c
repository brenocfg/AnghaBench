#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drbd_device {int /*<<< orphan*/  flags; int /*<<< orphan*/  rs_pending_cnt; int /*<<< orphan*/  ap_pending_cnt; int /*<<< orphan*/  local_cnt; TYPE_4__* ldev; } ;
struct backing_dev_info {int dummy; } ;
typedef  int sector_t ;
typedef  enum drbd_read_balancing { ____Placeholder_drbd_read_balancing } drbd_read_balancing ;
struct TYPE_8__ {TYPE_3__* backing_bdev; } ;
struct TYPE_7__ {TYPE_2__* bd_disk; } ;
struct TYPE_6__ {TYPE_1__* queue; } ;
struct TYPE_5__ {struct backing_dev_info* backing_dev_info; } ;

/* Variables and functions */
#define  RB_128K_STRIPING 138 
#define  RB_1M_STRIPING 137 
#define  RB_256K_STRIPING 136 
#define  RB_32K_STRIPING 135 
#define  RB_512K_STRIPING 134 
#define  RB_64K_STRIPING 133 
#define  RB_CONGESTED_REMOTE 132 
#define  RB_LEAST_PENDING 131 
#define  RB_PREFER_LOCAL 130 
#define  RB_PREFER_REMOTE 129 
#define  RB_ROUND_ROBIN 128 
 int /*<<< orphan*/  READ_BALANCE_RR ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int bdi_read_congested (struct backing_dev_info*) ; 
 int test_and_change_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool remote_due_to_read_balancing(struct drbd_device *device, sector_t sector,
		enum drbd_read_balancing rbm)
{
	struct backing_dev_info *bdi;
	int stripe_shift;

	switch (rbm) {
	case RB_CONGESTED_REMOTE:
		bdi = device->ldev->backing_bdev->bd_disk->queue->backing_dev_info;
		return bdi_read_congested(bdi);
	case RB_LEAST_PENDING:
		return atomic_read(&device->local_cnt) >
			atomic_read(&device->ap_pending_cnt) + atomic_read(&device->rs_pending_cnt);
	case RB_32K_STRIPING:  /* stripe_shift = 15 */
	case RB_64K_STRIPING:
	case RB_128K_STRIPING:
	case RB_256K_STRIPING:
	case RB_512K_STRIPING:
	case RB_1M_STRIPING:   /* stripe_shift = 20 */
		stripe_shift = (rbm - RB_32K_STRIPING + 15);
		return (sector >> (stripe_shift - 9)) & 1;
	case RB_ROUND_ROBIN:
		return test_and_change_bit(READ_BALANCE_RR, &device->flags);
	case RB_PREFER_REMOTE:
		return true;
	case RB_PREFER_LOCAL:
	default:
		return false;
	}
}