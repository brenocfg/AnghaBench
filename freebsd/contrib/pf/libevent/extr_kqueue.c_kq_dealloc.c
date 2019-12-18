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
struct kqop {scalar_t__ kq; struct kqop* events; struct kqop* changes; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  free (struct kqop*) ; 
 int /*<<< orphan*/  memset (struct kqop*,int /*<<< orphan*/ ,int) ; 

void
kq_dealloc(void *arg)
{
	struct kqop *kqop = arg;

	if (kqop->changes)
		free(kqop->changes);
	if (kqop->events)
		free(kqop->events);
	if (kqop->kq)
		close(kqop->kq);
	memset(kqop, 0, sizeof(struct kqop));
	free(kqop);
}