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
struct remote_lock {int refreshing; int /*<<< orphan*/  start_time; int /*<<< orphan*/  url; } ;
struct curl_slist {int dummy; } ;
struct active_request_slot {int /*<<< orphan*/  curl; struct slot_results* results; } ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLOPT_HTTPHEADER ; 
 int DAV_HEADER_IF ; 
 int DAV_HEADER_TIMEOUT ; 
 int /*<<< orphan*/  DAV_LOCK ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct curl_slist*) ; 
 int /*<<< orphan*/  curl_setup_http_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_slist_free_all (struct curl_slist*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct active_request_slot* get_active_slot () ; 
 struct curl_slist* get_dav_token_headers (struct remote_lock*,int) ; 
 int /*<<< orphan*/  run_active_slot (struct active_request_slot*) ; 
 scalar_t__ start_active_slot (struct active_request_slot*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int refresh_lock(struct remote_lock *lock)
{
	struct active_request_slot *slot;
	struct slot_results results;
	struct curl_slist *dav_headers;
	int rc = 0;

	lock->refreshing = 1;

	dav_headers = get_dav_token_headers(lock, DAV_HEADER_IF | DAV_HEADER_TIMEOUT);

	slot = get_active_slot();
	slot->results = &results;
	curl_setup_http_get(slot->curl, lock->url, DAV_LOCK);
	curl_easy_setopt(slot->curl, CURLOPT_HTTPHEADER, dav_headers);

	if (start_active_slot(slot)) {
		run_active_slot(slot);
		if (results.curl_result != CURLE_OK) {
			fprintf(stderr, "LOCK HTTP error %ld\n",
				results.http_code);
		} else {
			lock->start_time = time(NULL);
			rc = 1;
		}
	}

	lock->refreshing = 0;
	curl_slist_free_all(dav_headers);

	return rc;
}