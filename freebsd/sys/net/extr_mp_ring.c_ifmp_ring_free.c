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
struct ifmp_ring {int /*<<< orphan*/  mt; int /*<<< orphan*/ * abdications; int /*<<< orphan*/ * restarts; int /*<<< orphan*/ * stalls; int /*<<< orphan*/ * starts; int /*<<< orphan*/ * drops; int /*<<< orphan*/ * enqueues; } ;

/* Variables and functions */
 int /*<<< orphan*/  counter_u64_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct ifmp_ring*,int /*<<< orphan*/ ) ; 

void
ifmp_ring_free(struct ifmp_ring *r)
{

	if (r == NULL)
		return;

	if (r->enqueues != NULL)
		counter_u64_free(r->enqueues);
	if (r->drops != NULL)
		counter_u64_free(r->drops);
	if (r->starts != NULL)
		counter_u64_free(r->starts);
	if (r->stalls != NULL)
		counter_u64_free(r->stalls);
	if (r->restarts != NULL)
		counter_u64_free(r->restarts);
	if (r->abdications != NULL)
		counter_u64_free(r->abdications);

	free(r, r->mt);
}