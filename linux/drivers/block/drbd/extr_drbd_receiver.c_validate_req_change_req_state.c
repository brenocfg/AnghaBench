#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct rb_root {int dummy; } ;
struct drbd_request {int dummy; } ;
struct drbd_device {TYPE_1__* resource; } ;
struct bio_and_error {scalar_t__ bio; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  enum drbd_req_event { ____Placeholder_drbd_req_event } drbd_req_event ;
struct TYPE_2__ {int /*<<< orphan*/  req_lock; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  __req_mod (struct drbd_request*,int,struct bio_and_error*) ; 
 int /*<<< orphan*/  complete_master_bio (struct drbd_device*,struct bio_and_error*) ; 
 struct drbd_request* find_request (struct drbd_device*,struct rb_root*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
validate_req_change_req_state(struct drbd_device *device, u64 id, sector_t sector,
			      struct rb_root *root, const char *func,
			      enum drbd_req_event what, bool missing_ok)
{
	struct drbd_request *req;
	struct bio_and_error m;

	spin_lock_irq(&device->resource->req_lock);
	req = find_request(device, root, id, sector, missing_ok, func);
	if (unlikely(!req)) {
		spin_unlock_irq(&device->resource->req_lock);
		return -EIO;
	}
	__req_mod(req, what, &m);
	spin_unlock_irq(&device->resource->req_lock);

	if (m.bio)
		complete_master_bio(device, &m);
	return 0;
}