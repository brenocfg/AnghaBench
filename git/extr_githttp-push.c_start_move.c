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
struct transfer_request {char* dest; int /*<<< orphan*/  url; int /*<<< orphan*/  state; struct active_request_slot* slot; } ;
struct curl_slist {int dummy; } ;
struct active_request_slot {int /*<<< orphan*/  curl; struct transfer_request* callback_data; int /*<<< orphan*/  callback_func; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABORTED ; 
 int /*<<< orphan*/  CURLOPT_HTTPHEADER ; 
 int /*<<< orphan*/  DAV_MOVE ; 
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUN_MOVE ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct curl_slist*) ; 
 int /*<<< orphan*/  curl_setup_http_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct curl_slist* curl_slist_append (struct curl_slist*,char*) ; 
 struct active_request_slot* get_active_slot () ; 
 struct curl_slist* http_copy_default_headers () ; 
 int /*<<< orphan*/  process_response ; 
 scalar_t__ start_active_slot (struct active_request_slot*) ; 

__attribute__((used)) static void start_move(struct transfer_request *request)
{
	struct active_request_slot *slot;
	struct curl_slist *dav_headers = http_copy_default_headers();

	slot = get_active_slot();
	slot->callback_func = process_response;
	slot->callback_data = request;
	curl_setup_http_get(slot->curl, request->url, DAV_MOVE);
	dav_headers = curl_slist_append(dav_headers, request->dest);
	dav_headers = curl_slist_append(dav_headers, "Overwrite: T");
	curl_easy_setopt(slot->curl, CURLOPT_HTTPHEADER, dav_headers);

	if (start_active_slot(slot)) {
		request->slot = slot;
		request->state = RUN_MOVE;
	} else {
		request->state = ABORTED;
		FREE_AND_NULL(request->url);
	}
}