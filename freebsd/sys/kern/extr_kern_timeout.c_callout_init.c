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
struct callout {int /*<<< orphan*/  c_cpu; scalar_t__ c_iflags; int /*<<< orphan*/ * c_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock_object; } ;

/* Variables and functions */
 scalar_t__ CALLOUT_RETURNUNLOCKED ; 
 TYPE_1__ Giant ; 
 int /*<<< orphan*/  bzero (struct callout*,int) ; 
 int /*<<< orphan*/  timeout_cpu ; 

void
callout_init(struct callout *c, int mpsafe)
{
	bzero(c, sizeof *c);
	if (mpsafe) {
		c->c_lock = NULL;
		c->c_iflags = CALLOUT_RETURNUNLOCKED;
	} else {
		c->c_lock = &Giant.lock_object;
		c->c_iflags = 0;
	}
	c->c_cpu = timeout_cpu;
}