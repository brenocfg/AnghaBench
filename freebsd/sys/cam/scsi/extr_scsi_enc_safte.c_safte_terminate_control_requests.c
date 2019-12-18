#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int result; } ;
typedef  TYPE_1__ safte_control_request_t ;
typedef  int /*<<< orphan*/  safte_control_reqlist_t ;

/* Variables and functions */
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  wakeup (TYPE_1__*) ; 

__attribute__((used)) static void
safte_terminate_control_requests(safte_control_reqlist_t *reqlist, int result)
{
	safte_control_request_t *req;

	while ((req = TAILQ_FIRST(reqlist)) != NULL) {
		TAILQ_REMOVE(reqlist, req, links);
		req->result = result;
		wakeup(req);
	}
}