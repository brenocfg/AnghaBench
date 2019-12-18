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
struct completion {int done; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int mtx_owned (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
_completion_claim(struct completion *c)
{

	KASSERT(mtx_owned(&c->lock),
	    ("_completion_claim should be called with acquired lock"));
	KASSERT(c->done != 0, ("_completion_claim on non-waited completion"));
	if (c->done > 0)
		c->done--;
	else
		KASSERT(c->done == -1, ("Invalid value of c->done: %d", c->done));
}