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
struct TYPE_2__ {int size; int /*<<< orphan*/  sector; } ;
struct drbd_peer_request {int flags; TYPE_1__ i; } ;
struct drbd_device {int dummy; } ;

/* Variables and functions */
 int EE_TRIM ; 
 int EE_WAS_ERROR ; 
 int EE_ZEROOUT ; 
 int /*<<< orphan*/  can_do_reliable_discards (struct drbd_device*) ; 
 int /*<<< orphan*/  drbd_endio_write_sec_final (struct drbd_peer_request*) ; 
 scalar_t__ drbd_issue_discard_or_zero_out (struct drbd_device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void drbd_issue_peer_discard_or_zero_out(struct drbd_device *device, struct drbd_peer_request *peer_req)
{
	/* If the backend cannot discard, or does not guarantee
	 * read-back zeroes in discarded ranges, we fall back to
	 * zero-out.  Unless configuration specifically requested
	 * otherwise. */
	if (!can_do_reliable_discards(device))
		peer_req->flags |= EE_ZEROOUT;

	if (drbd_issue_discard_or_zero_out(device, peer_req->i.sector,
	    peer_req->i.size >> 9, peer_req->flags & (EE_ZEROOUT|EE_TRIM)))
		peer_req->flags |= EE_WAS_ERROR;
	drbd_endio_write_sec_final(peer_req);
}