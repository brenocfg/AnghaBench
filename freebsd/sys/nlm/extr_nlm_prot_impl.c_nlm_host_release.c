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
struct nlm_host {int /*<<< orphan*/  nh_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  nlm_host_destroy (struct nlm_host*) ; 
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 

void nlm_host_release(struct nlm_host *host)
{
	if (refcount_release(&host->nh_refs)) {
		/*
		 * Free the host
		 */
		nlm_host_destroy(host);
	}
}