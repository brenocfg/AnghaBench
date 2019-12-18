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
struct active_request_slot {int* finished; int /*<<< orphan*/  callback_data; int /*<<< orphan*/  (* callback_func ) (int /*<<< orphan*/ ) ;TYPE_1__* results; int /*<<< orphan*/  curl; scalar_t__ http_code; int /*<<< orphan*/  curl_result; } ;
struct TYPE_2__ {scalar_t__ http_connectcode; scalar_t__ auth_avail; scalar_t__ http_code; int /*<<< orphan*/  curl_result; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURLINFO_HTTPAUTH_AVAIL ; 
 int /*<<< orphan*/  CURLINFO_HTTP_CODE ; 
 int /*<<< orphan*/  CURLINFO_HTTP_CONNECTCODE ; 
 int /*<<< orphan*/  closedown_active_slot (struct active_request_slot*) ; 
 int /*<<< orphan*/  curl_easy_getinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void finish_active_slot(struct active_request_slot *slot)
{
	closedown_active_slot(slot);
	curl_easy_getinfo(slot->curl, CURLINFO_HTTP_CODE, &slot->http_code);

	if (slot->finished != NULL)
		(*slot->finished) = 1;

	/* Store slot results so they can be read after the slot is reused */
	if (slot->results != NULL) {
		slot->results->curl_result = slot->curl_result;
		slot->results->http_code = slot->http_code;
#if LIBCURL_VERSION_NUM >= 0x070a08
		curl_easy_getinfo(slot->curl, CURLINFO_HTTPAUTH_AVAIL,
				  &slot->results->auth_avail);
#else
		slot->results->auth_avail = 0;
#endif

		curl_easy_getinfo(slot->curl, CURLINFO_HTTP_CONNECTCODE,
			&slot->results->http_connectcode);
	}

	/* Run callback if appropriate */
	if (slot->callback_func != NULL)
		slot->callback_func(slot->callback_data);
}