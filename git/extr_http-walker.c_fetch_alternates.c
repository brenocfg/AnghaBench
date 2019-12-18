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
struct walker_data {int got_alternates; } ;
struct walker {scalar_t__ get_verbosely; struct walker_data* data; } ;
struct strbuf {struct strbuf* buf; } ;
struct alternates_request {char const* base; int http_specific; struct active_request_slot* slot; struct strbuf* buffer; struct strbuf* url; struct walker* walker; } ;
struct active_request_slot {int /*<<< orphan*/  curl; struct alternates_request* callback_data; int /*<<< orphan*/  callback_func; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_FILE ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_WRITEFUNCTION ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 struct strbuf* fwrite_buffer ; 
 struct active_request_slot* get_active_slot () ; 
 int /*<<< orphan*/  process_alternates_response ; 
 int /*<<< orphan*/  run_active_slot (struct active_request_slot*) ; 
 scalar_t__ start_active_slot (struct active_request_slot*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  step_active_slots () ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void fetch_alternates(struct walker *walker, const char *base)
{
	struct strbuf buffer = STRBUF_INIT;
	struct strbuf url = STRBUF_INIT;
	struct active_request_slot *slot;
	struct alternates_request alt_req;
	struct walker_data *cdata = walker->data;

	/*
	 * If another request has already started fetching alternates,
	 * wait for them to arrive and return to processing this request's
	 * curl message
	 */
#ifdef USE_CURL_MULTI
	while (cdata->got_alternates == 0) {
		step_active_slots();
	}
#endif

	/* Nothing to do if they've already been fetched */
	if (cdata->got_alternates == 1)
		return;

	/* Start the fetch */
	cdata->got_alternates = 0;

	if (walker->get_verbosely)
		fprintf(stderr, "Getting alternates list for %s\n", base);

	strbuf_addf(&url, "%s/objects/info/http-alternates", base);

	/*
	 * Use a callback to process the result, since another request
	 * may fail and need to have alternates loaded before continuing
	 */
	slot = get_active_slot();
	slot->callback_func = process_alternates_response;
	alt_req.walker = walker;
	slot->callback_data = &alt_req;

	curl_easy_setopt(slot->curl, CURLOPT_FILE, &buffer);
	curl_easy_setopt(slot->curl, CURLOPT_WRITEFUNCTION, fwrite_buffer);
	curl_easy_setopt(slot->curl, CURLOPT_URL, url.buf);

	alt_req.base = base;
	alt_req.url = &url;
	alt_req.buffer = &buffer;
	alt_req.http_specific = 1;
	alt_req.slot = slot;

	if (start_active_slot(slot))
		run_active_slot(slot);
	else
		cdata->got_alternates = -1;

	strbuf_release(&buffer);
	strbuf_release(&url);
}