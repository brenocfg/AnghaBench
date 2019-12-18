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
struct evdns_request {int /*<<< orphan*/ * search_origname; int /*<<< orphan*/ * search_state; TYPE_1__* current_req; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_LOCKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  search_state_decref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
search_request_finished(struct evdns_request *const handle) {
	ASSERT_LOCKED(handle->current_req->base);
	if (handle->search_state) {
		search_state_decref(handle->search_state);
		handle->search_state = NULL;
	}
	if (handle->search_origname) {
		mm_free(handle->search_origname);
		handle->search_origname = NULL;
	}
}