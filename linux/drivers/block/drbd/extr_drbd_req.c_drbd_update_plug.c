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
struct drbd_request {int /*<<< orphan*/  kref; } ;
struct drbd_plug_cb {struct drbd_request* most_recent_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  drbd_req_destroy ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drbd_update_plug(struct drbd_plug_cb *plug, struct drbd_request *req)
{
	struct drbd_request *tmp = plug->most_recent_req;
	/* Will be sent to some peer.
	 * Remember to tag it with UNPLUG_REMOTE on unplug */
	kref_get(&req->kref);
	plug->most_recent_req = req;
	if (tmp)
		kref_put(&tmp->kref, drbd_req_destroy);
}