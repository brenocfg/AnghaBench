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
struct strbuf {int /*<<< orphan*/  buf; scalar_t__ len; } ;
struct slot_results {int http_code; int curl_result; } ;
struct active_request_slot {int dummy; } ;

/* Variables and functions */
 int CURLE_OK ; 
 int HTTP_OK ; 
 int HTTP_REAUTH ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__* curl_errorstr ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int run_one_slot (struct active_request_slot*,struct slot_results*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,scalar_t__*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int run_slot(struct active_request_slot *slot,
		    struct slot_results *results)
{
	int err;
	struct slot_results results_buf;

	if (!results)
		results = &results_buf;

	err = run_one_slot(slot, results);

	if (err != HTTP_OK && err != HTTP_REAUTH) {
		struct strbuf msg = STRBUF_INIT;
		if (results->http_code && results->http_code != 200)
			strbuf_addf(&msg, "HTTP %ld", results->http_code);
		if (results->curl_result != CURLE_OK) {
			if (msg.len)
				strbuf_addch(&msg, ' ');
			strbuf_addf(&msg, "curl %d", results->curl_result);
			if (curl_errorstr[0]) {
				strbuf_addch(&msg, ' ');
				strbuf_addstr(&msg, curl_errorstr);
			}
		}
		error(_("RPC failed; %s"), msg.buf);
		strbuf_release(&msg);
	}

	return err;
}