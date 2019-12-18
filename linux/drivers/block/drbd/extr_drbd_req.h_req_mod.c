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
struct drbd_request {struct drbd_device* device; } ;
struct drbd_device {TYPE_1__* resource; } ;
struct bio_and_error {scalar_t__ bio; } ;
typedef  enum drbd_req_event { ____Placeholder_drbd_req_event } drbd_req_event ;
struct TYPE_2__ {int /*<<< orphan*/  req_lock; } ;

/* Variables and functions */
 int __req_mod (struct drbd_request*,int,struct bio_and_error*) ; 
 int /*<<< orphan*/  complete_master_bio (struct drbd_device*,struct bio_and_error*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline int req_mod(struct drbd_request *req,
		enum drbd_req_event what)
{
	unsigned long flags;
	struct drbd_device *device = req->device;
	struct bio_and_error m;
	int rv;

	spin_lock_irqsave(&device->resource->req_lock, flags);
	rv = __req_mod(req, what, &m);
	spin_unlock_irqrestore(&device->resource->req_lock, flags);

	if (m.bio)
		complete_master_bio(device, &m);

	return rv;
}