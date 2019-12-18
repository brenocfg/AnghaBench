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
struct drbd_request {int dummy; } ;
struct drbd_device {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct drbd_request*) ; 
 struct drbd_request* drbd_request_prepare (struct drbd_device*,struct bio*,unsigned long) ; 
 int /*<<< orphan*/  drbd_send_and_submit (struct drbd_device*,struct drbd_request*) ; 

void __drbd_make_request(struct drbd_device *device, struct bio *bio, unsigned long start_jif)
{
	struct drbd_request *req = drbd_request_prepare(device, bio, start_jif);
	if (IS_ERR_OR_NULL(req))
		return;
	drbd_send_and_submit(device, req);
}