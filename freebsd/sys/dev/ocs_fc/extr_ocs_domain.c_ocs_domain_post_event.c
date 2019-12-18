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
typedef  int /*<<< orphan*/  ocs_sm_event_t ;
struct TYPE_5__ {int req_domain_free; int req_accept_frames; int /*<<< orphan*/  drvsm; } ;
typedef  TYPE_1__ ocs_domain_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_domain_accept_frames (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_domain_free (TYPE_1__*) ; 
 int ocs_sm_post_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

int
ocs_domain_post_event(ocs_domain_t *domain, ocs_sm_event_t event, void *arg)
{
	int rc;
	int accept_frames;
	int req_domain_free;

	rc = ocs_sm_post_event(&domain->drvsm, event, arg);

	req_domain_free = domain->req_domain_free;
	domain->req_domain_free = 0;

	accept_frames = domain->req_accept_frames;
	domain->req_accept_frames = 0;

	if (accept_frames) {
		ocs_domain_accept_frames(domain);
	}

	if (req_domain_free) {
		ocs_domain_free(domain);
	}

	return rc;
}