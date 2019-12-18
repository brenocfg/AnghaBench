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
struct active_request_slot {int in_use; int /*<<< orphan*/ * curl; int /*<<< orphan*/ * callback_func; int /*<<< orphan*/ * callback_data; int /*<<< orphan*/ * finished; int /*<<< orphan*/ * results; struct active_request_slot* next; } ;
struct TYPE_2__ {scalar_t__ password; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_COOKIEFILE ; 
 int /*<<< orphan*/  CURLOPT_COOKIEJAR ; 
 int /*<<< orphan*/  CURLOPT_CUSTOMREQUEST ; 
 int /*<<< orphan*/  CURLOPT_ERRORBUFFER ; 
 int /*<<< orphan*/  CURLOPT_FAILONERROR ; 
 int /*<<< orphan*/  CURLOPT_FOLLOWLOCATION ; 
 int /*<<< orphan*/  CURLOPT_HTTPAUTH ; 
 int /*<<< orphan*/  CURLOPT_HTTPGET ; 
 int /*<<< orphan*/  CURLOPT_HTTPHEADER ; 
 int /*<<< orphan*/  CURLOPT_IPRESOLVE ; 
 int /*<<< orphan*/  CURLOPT_POSTFIELDS ; 
 int /*<<< orphan*/  CURLOPT_RANGE ; 
 int /*<<< orphan*/  CURLOPT_READFUNCTION ; 
 int /*<<< orphan*/  CURLOPT_UPLOAD ; 
 int /*<<< orphan*/  CURLOPT_WRITEFUNCTION ; 
 scalar_t__ HTTP_FOLLOW_ALWAYS ; 
 struct active_request_slot* active_queue_head ; 
 int active_requests ; 
 int curl_cookie_file ; 
 int /*<<< orphan*/  curl_default ; 
 int /*<<< orphan*/ * curl_easy_duphandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ curl_empty_auth_enabled () ; 
 int curl_errorstr ; 
 int /*<<< orphan*/  curl_multi_perform (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ curl_save_cookies ; 
 int /*<<< orphan*/  curl_session_count ; 
 int /*<<< orphan*/  curlm ; 
 int /*<<< orphan*/ * get_curl_handle () ; 
 int git_curl_ipresolve ; 
 TYPE_1__ http_auth ; 
 int http_auth_methods ; 
 scalar_t__ http_follow_config ; 
 int /*<<< orphan*/  init_curl_http_auth (int /*<<< orphan*/ *) ; 
 int max_requests ; 
 int pragma_header ; 
 int /*<<< orphan*/  process_curl_messages () ; 
 struct active_request_slot* xmalloc (int) ; 

struct active_request_slot *get_active_slot(void)
{
	struct active_request_slot *slot = active_queue_head;
	struct active_request_slot *newslot;

#ifdef USE_CURL_MULTI
	int num_transfers;

	/* Wait for a slot to open up if the queue is full */
	while (active_requests >= max_requests) {
		curl_multi_perform(curlm, &num_transfers);
		if (num_transfers < active_requests)
			process_curl_messages();
	}
#endif

	while (slot != NULL && slot->in_use)
		slot = slot->next;

	if (slot == NULL) {
		newslot = xmalloc(sizeof(*newslot));
		newslot->curl = NULL;
		newslot->in_use = 0;
		newslot->next = NULL;

		slot = active_queue_head;
		if (slot == NULL) {
			active_queue_head = newslot;
		} else {
			while (slot->next != NULL)
				slot = slot->next;
			slot->next = newslot;
		}
		slot = newslot;
	}

	if (slot->curl == NULL) {
#ifdef NO_CURL_EASY_DUPHANDLE
		slot->curl = get_curl_handle();
#else
		slot->curl = curl_easy_duphandle(curl_default);
#endif
		curl_session_count++;
	}

	active_requests++;
	slot->in_use = 1;
	slot->results = NULL;
	slot->finished = NULL;
	slot->callback_data = NULL;
	slot->callback_func = NULL;
	curl_easy_setopt(slot->curl, CURLOPT_COOKIEFILE, curl_cookie_file);
	if (curl_save_cookies)
		curl_easy_setopt(slot->curl, CURLOPT_COOKIEJAR, curl_cookie_file);
	curl_easy_setopt(slot->curl, CURLOPT_HTTPHEADER, pragma_header);
	curl_easy_setopt(slot->curl, CURLOPT_ERRORBUFFER, curl_errorstr);
	curl_easy_setopt(slot->curl, CURLOPT_CUSTOMREQUEST, NULL);
	curl_easy_setopt(slot->curl, CURLOPT_READFUNCTION, NULL);
	curl_easy_setopt(slot->curl, CURLOPT_WRITEFUNCTION, NULL);
	curl_easy_setopt(slot->curl, CURLOPT_POSTFIELDS, NULL);
	curl_easy_setopt(slot->curl, CURLOPT_UPLOAD, 0);
	curl_easy_setopt(slot->curl, CURLOPT_HTTPGET, 1);
	curl_easy_setopt(slot->curl, CURLOPT_FAILONERROR, 1);
	curl_easy_setopt(slot->curl, CURLOPT_RANGE, NULL);

	/*
	 * Default following to off unless "ALWAYS" is configured; this gives
	 * callers a sane starting point, and they can tweak for individual
	 * HTTP_FOLLOW_* cases themselves.
	 */
	if (http_follow_config == HTTP_FOLLOW_ALWAYS)
		curl_easy_setopt(slot->curl, CURLOPT_FOLLOWLOCATION, 1);
	else
		curl_easy_setopt(slot->curl, CURLOPT_FOLLOWLOCATION, 0);

#if LIBCURL_VERSION_NUM >= 0x070a08
	curl_easy_setopt(slot->curl, CURLOPT_IPRESOLVE, git_curl_ipresolve);
#endif
#ifdef LIBCURL_CAN_HANDLE_AUTH_ANY
	curl_easy_setopt(slot->curl, CURLOPT_HTTPAUTH, http_auth_methods);
#endif
	if (http_auth.password || curl_empty_auth_enabled())
		init_curl_http_auth(slot->curl);

	return slot;
}