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
struct callout_cpu {int /*<<< orphan*/  cc_callfree; } ;
struct callout {int c_iflags; int /*<<< orphan*/ * c_func; } ;
struct TYPE_2__ {int /*<<< orphan*/  sle; } ;

/* Variables and functions */
 int CALLOUT_LOCAL_ALLOC ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct callout*,int /*<<< orphan*/ ) ; 
 TYPE_1__ c_links ; 

__attribute__((used)) static void
callout_cc_del(struct callout *c, struct callout_cpu *cc)
{

	if ((c->c_iflags & CALLOUT_LOCAL_ALLOC) == 0)
		return;
	c->c_func = NULL;
	SLIST_INSERT_HEAD(&cc->cc_callfree, c, c_links.sle);
}