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
struct transfer_request {struct transfer_request* next; int /*<<< orphan*/  state; int /*<<< orphan*/ * headers; int /*<<< orphan*/ * lock; int /*<<< orphan*/ * url; struct object* obj; } ;
struct TYPE_2__ {size_t* hash; } ;
struct object {int flags; TYPE_1__ oid; } ;

/* Variables and functions */
 int FETCHING ; 
 int LOCAL ; 
 int /*<<< orphan*/  NEED_FETCH ; 
 int /*<<< orphan*/  check_locks () ; 
 int /*<<< orphan*/  fill_active_slots () ; 
 int /*<<< orphan*/  get_remote_object_list (size_t) ; 
 int* remote_dir_exists ; 
 struct transfer_request* request_queue_head ; 
 int /*<<< orphan*/  step_active_slots () ; 
 struct transfer_request* xmalloc (int) ; 

__attribute__((used)) static void add_fetch_request(struct object *obj)
{
	struct transfer_request *request;

	check_locks();

	/*
	 * Don't fetch the object if it's known to exist locally
	 * or is already in the request queue
	 */
	if (remote_dir_exists[obj->oid.hash[0]] == -1)
		get_remote_object_list(obj->oid.hash[0]);
	if (obj->flags & (LOCAL | FETCHING))
		return;

	obj->flags |= FETCHING;
	request = xmalloc(sizeof(*request));
	request->obj = obj;
	request->url = NULL;
	request->lock = NULL;
	request->headers = NULL;
	request->state = NEED_FETCH;
	request->next = request_queue_head;
	request_queue_head = request;

#ifdef USE_CURL_MULTI
	fill_active_slots();
	step_active_slots();
#endif
}