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
struct walker_data {int /*<<< orphan*/  alt; } ;
struct walker {int /*<<< orphan*/  get_verbosely; struct walker_data* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  hash; } ;
struct object_request {int /*<<< orphan*/  node; int /*<<< orphan*/ * req; int /*<<< orphan*/  state; int /*<<< orphan*/  repo; TYPE_1__ oid; struct walker* walker; } ;

/* Variables and functions */
 int /*<<< orphan*/  WAITING ; 
 int /*<<< orphan*/  fill_active_slots () ; 
 int /*<<< orphan*/  hashcpy (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  http_is_verbose ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  object_queue_head ; 
 int /*<<< orphan*/  step_active_slots () ; 
 struct object_request* xmalloc (int) ; 

__attribute__((used)) static void prefetch(struct walker *walker, unsigned char *sha1)
{
	struct object_request *newreq;
	struct walker_data *data = walker->data;

	newreq = xmalloc(sizeof(*newreq));
	newreq->walker = walker;
	hashcpy(newreq->oid.hash, sha1);
	newreq->repo = data->alt;
	newreq->state = WAITING;
	newreq->req = NULL;

	http_is_verbose = walker->get_verbosely;
	list_add_tail(&newreq->node, &object_queue_head);

#ifdef USE_CURL_MULTI
	fill_active_slots();
	step_active_slots();
#endif
}