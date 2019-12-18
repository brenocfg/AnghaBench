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
struct TYPE_2__ {int flags; } ;
struct dn_schk {scalar_t__ siht; TYPE_1__ sch; } ;

/* Variables and functions */
 int DN_HAVE_MASK ; 
 int /*<<< orphan*/  dn_ht_scan (scalar_t__,int /*<<< orphan*/  (*) (scalar_t__,int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  si_reset_credit (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
schk_reset_credit(struct dn_schk *s)
{
	if (s->sch.flags & DN_HAVE_MASK)
		dn_ht_scan(s->siht, si_reset_credit, NULL);
	else if (s->siht)
		si_reset_credit(s->siht, NULL);
}