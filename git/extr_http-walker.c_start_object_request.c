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
struct walker {int dummy; } ;
struct object_request {void* state; struct http_object_request* req; int /*<<< orphan*/  oid; TYPE_1__* repo; } ;
struct http_object_request {struct active_request_slot* slot; } ;
struct active_request_slot {struct object_request* callback_data; int /*<<< orphan*/  callback_func; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 void* ABORTED ; 
 void* ACTIVE ; 
 struct http_object_request* new_http_object_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_object_response ; 
 int /*<<< orphan*/  release_http_object_request (struct http_object_request*) ; 
 int /*<<< orphan*/  start_active_slot (struct active_request_slot*) ; 

__attribute__((used)) static void start_object_request(struct walker *walker,
				 struct object_request *obj_req)
{
	struct active_request_slot *slot;
	struct http_object_request *req;

	req = new_http_object_request(obj_req->repo->base, &obj_req->oid);
	if (req == NULL) {
		obj_req->state = ABORTED;
		return;
	}
	obj_req->req = req;

	slot = req->slot;
	slot->callback_func = process_object_response;
	slot->callback_data = obj_req;

	/* Try to get the request started, abort the request on error */
	obj_req->state = ACTIVE;
	if (!start_active_slot(slot)) {
		obj_req->state = ABORTED;
		release_http_object_request(req);
		return;
	}
}