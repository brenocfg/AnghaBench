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
struct completion {scalar_t__ done; int /*<<< orphan*/  lock; int /*<<< orphan*/  cv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 

void
init_completion(struct completion *c)
{
	cv_init(&c->cv, "VCHI completion cv");
	mtx_init(&c->lock, "VCHI completion lock", "condvar", MTX_DEF);
	c->done = 0;
}