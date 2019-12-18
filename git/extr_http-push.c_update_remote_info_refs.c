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
struct slot_results {scalar_t__ curl_result; int /*<<< orphan*/  http_code; } ;
struct remote_lock {int /*<<< orphan*/  url; } ;
struct curl_slist {int dummy; } ;
struct buffer {int /*<<< orphan*/  buf; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct active_request_slot {int /*<<< orphan*/  curl; struct slot_results* results; } ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLOPT_HTTPHEADER ; 
 int /*<<< orphan*/  DAV_HEADER_IF ; 
 int /*<<< orphan*/  DAV_PUT ; 
 int PROCESS_FILES ; 
 int RECURSIVE ; 
 int /*<<< orphan*/  STRBUF_INIT ; 
 int /*<<< orphan*/  aborted ; 
 int /*<<< orphan*/  add_remote_info_ref ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct curl_slist*) ; 
 int /*<<< orphan*/  curl_setup_http (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite_null ; 
 struct active_request_slot* get_active_slot () ; 
 struct curl_slist* get_dav_token_headers (struct remote_lock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remote_ls (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_active_slot (struct active_request_slot*) ; 
 scalar_t__ start_active_slot (struct active_request_slot*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_remote_info_refs(struct remote_lock *lock)
{
	struct buffer buffer = { STRBUF_INIT, 0 };
	struct active_request_slot *slot;
	struct slot_results results;
	struct curl_slist *dav_headers;

	remote_ls("refs/", (PROCESS_FILES | RECURSIVE),
		  add_remote_info_ref, &buffer.buf);
	if (!aborted) {
		dav_headers = get_dav_token_headers(lock, DAV_HEADER_IF);

		slot = get_active_slot();
		slot->results = &results;
		curl_setup_http(slot->curl, lock->url, DAV_PUT,
				&buffer, fwrite_null);
		curl_easy_setopt(slot->curl, CURLOPT_HTTPHEADER, dav_headers);

		if (start_active_slot(slot)) {
			run_active_slot(slot);
			if (results.curl_result != CURLE_OK) {
				fprintf(stderr,
					"PUT error: curl result=%d, HTTP code=%ld\n",
					results.curl_result, results.http_code);
			}
		}
	}
	strbuf_release(&buffer.buf);
}