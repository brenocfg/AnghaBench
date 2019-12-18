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
struct active_request_slot {scalar_t__ in_use; int /*<<< orphan*/  curl; } ;
typedef  scalar_t__ CURLMcode ;

/* Variables and functions */
 scalar_t__ CURLM_CALL_MULTI_PERFORM ; 
 scalar_t__ CURLM_OK ; 
 int /*<<< orphan*/  active_requests ; 
 scalar_t__ curl_multi_add_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_multi_perform (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  curl_multi_strerror (scalar_t__) ; 
 int /*<<< orphan*/  curlm ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

int start_active_slot(struct active_request_slot *slot)
{
#ifdef USE_CURL_MULTI
	CURLMcode curlm_result = curl_multi_add_handle(curlm, slot->curl);
	int num_transfers;

	if (curlm_result != CURLM_OK &&
	    curlm_result != CURLM_CALL_MULTI_PERFORM) {
		warning("curl_multi_add_handle failed: %s",
			curl_multi_strerror(curlm_result));
		active_requests--;
		slot->in_use = 0;
		return 0;
	}

	/*
	 * We know there must be something to do, since we just added
	 * something.
	 */
	curl_multi_perform(curlm, &num_transfers);
#endif
	return 1;
}