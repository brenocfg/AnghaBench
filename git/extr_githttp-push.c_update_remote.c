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
struct object_id {int dummy; } ;
struct curl_slist {int dummy; } ;
struct buffer {int /*<<< orphan*/  buf; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct active_request_slot {int /*<<< orphan*/  curl; struct slot_results* results; } ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLOPT_HTTPHEADER ; 
 int /*<<< orphan*/  DAV_HEADER_IF ; 
 int /*<<< orphan*/  DAV_PUT ; 
 int /*<<< orphan*/  STRBUF_INIT ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct curl_slist*) ; 
 int /*<<< orphan*/  curl_setup_http (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fwrite_null ; 
 struct active_request_slot* get_active_slot () ; 
 struct curl_slist* get_dav_token_headers (struct remote_lock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  run_active_slot (struct active_request_slot*) ; 
 scalar_t__ start_active_slot (struct active_request_slot*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_addf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int update_remote(const struct object_id *oid, struct remote_lock *lock)
{
	struct active_request_slot *slot;
	struct slot_results results;
	struct buffer out_buffer = { STRBUF_INIT, 0 };
	struct curl_slist *dav_headers;

	dav_headers = get_dav_token_headers(lock, DAV_HEADER_IF);

	strbuf_addf(&out_buffer.buf, "%s\n", oid_to_hex(oid));

	slot = get_active_slot();
	slot->results = &results;
	curl_setup_http(slot->curl, lock->url, DAV_PUT,
			&out_buffer, fwrite_null);
	curl_easy_setopt(slot->curl, CURLOPT_HTTPHEADER, dav_headers);

	if (start_active_slot(slot)) {
		run_active_slot(slot);
		strbuf_release(&out_buffer.buf);
		if (results.curl_result != CURLE_OK) {
			fprintf(stderr,
				"PUT error: curl result=%d, HTTP code=%ld\n",
				results.curl_result, results.http_code);
			/* We should attempt recovery? */
			return 0;
		}
	} else {
		strbuf_release(&out_buffer.buf);
		fprintf(stderr, "Unable to start PUT request\n");
		return 0;
	}

	return 1;
}