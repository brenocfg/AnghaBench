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
struct active_request_slot {int /*<<< orphan*/ * curl; } ;

/* Variables and functions */
 int /*<<< orphan*/  closedown_active_slot (struct active_request_slot*) ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 scalar_t__ curl_session_count ; 
 int /*<<< orphan*/  fill_active_slots () ; 
 scalar_t__ min_curl_sessions ; 
 int /*<<< orphan*/  xmulti_remove_handle (struct active_request_slot*) ; 

__attribute__((used)) static void release_active_slot(struct active_request_slot *slot)
{
	closedown_active_slot(slot);
	if (slot->curl) {
		xmulti_remove_handle(slot);
		if (curl_session_count > min_curl_sessions) {
			curl_easy_cleanup(slot->curl);
			slot->curl = NULL;
			curl_session_count--;
		}
	}
#ifdef USE_CURL_MULTI
	fill_active_slots();
#endif
}