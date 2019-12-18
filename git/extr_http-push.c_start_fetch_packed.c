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
struct transfer_request {scalar_t__ state; struct http_pack_request* userData; TYPE_2__* slot; struct transfer_request* next; int /*<<< orphan*/  url; TYPE_1__* obj; } ;
struct packed_git {int /*<<< orphan*/  hash; } ;
struct http_pack_request {TYPE_2__* slot; int /*<<< orphan*/  url; int /*<<< orphan*/ * lst; } ;
struct TYPE_8__ {int /*<<< orphan*/  hash; } ;
struct TYPE_7__ {scalar_t__ can_update_info_refs; int /*<<< orphan*/  packs; int /*<<< orphan*/  url; } ;
struct TYPE_6__ {struct transfer_request* callback_data; int /*<<< orphan*/  callback_func; } ;
struct TYPE_5__ {TYPE_4__ oid; } ;

/* Variables and functions */
 scalar_t__ RUN_FETCH_PACKED ; 
 struct packed_git* find_sha1_pack (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* hash_to_hex (int /*<<< orphan*/ ) ; 
 struct http_pack_request* new_http_pack_request (struct packed_git*,int /*<<< orphan*/ ) ; 
 char* oid_to_hex (TYPE_4__*) ; 
 int /*<<< orphan*/  process_response ; 
 int /*<<< orphan*/  release_http_pack_request (struct http_pack_request*) ; 
 int /*<<< orphan*/  release_request (struct transfer_request*) ; 
 TYPE_3__* repo ; 
 struct transfer_request* request_queue_head ; 
 int /*<<< orphan*/  start_active_slot (TYPE_2__*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void start_fetch_packed(struct transfer_request *request)
{
	struct packed_git *target;

	struct transfer_request *check_request = request_queue_head;
	struct http_pack_request *preq;

	target = find_sha1_pack(request->obj->oid.hash, repo->packs);
	if (!target) {
		fprintf(stderr, "Unable to fetch %s, will not be able to update server info refs\n", oid_to_hex(&request->obj->oid));
		repo->can_update_info_refs = 0;
		release_request(request);
		return;
	}

	fprintf(stderr,	"Fetching pack %s\n",
		hash_to_hex(target->hash));
	fprintf(stderr, " which contains %s\n", oid_to_hex(&request->obj->oid));

	preq = new_http_pack_request(target, repo->url);
	if (preq == NULL) {
		repo->can_update_info_refs = 0;
		return;
	}
	preq->lst = &repo->packs;

	/* Make sure there isn't another open request for this pack */
	while (check_request) {
		if (check_request->state == RUN_FETCH_PACKED &&
		    !strcmp(check_request->url, preq->url)) {
			release_http_pack_request(preq);
			release_request(request);
			return;
		}
		check_request = check_request->next;
	}

	preq->slot->callback_func = process_response;
	preq->slot->callback_data = request;
	request->slot = preq->slot;
	request->userData = preq;

	/* Try to get the request started, abort the request on error */
	request->state = RUN_FETCH_PACKED;
	if (!start_active_slot(preq->slot)) {
		fprintf(stderr, "Unable to start GET request\n");
		release_http_pack_request(preq);
		repo->can_update_info_refs = 0;
		release_request(request);
	}
}