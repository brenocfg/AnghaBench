#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hpriv_p ;
struct TYPE_4__ {int /*<<< orphan*/  hook; int /*<<< orphan*/  node; int /*<<< orphan*/  reorderTimer; } ;

/* Variables and functions */
 int hz ; 
 int /*<<< orphan*/  ng_callout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_pptpgre_reorder_timeout ; 
 int reorder_timeout ; 

__attribute__((used)) static void
ng_pptpgre_start_reorder_timer(hpriv_p hpriv)
{
	int ticks;

	/* Be conservative: timeout can happen up to 1 tick early */
	ticks = (((reorder_timeout * hz) + 1000 - 1) / 1000) + 1;
	ng_callout(&hpriv->reorderTimer, hpriv->node, hpriv->hook,
		ticks, ng_pptpgre_reorder_timeout, hpriv, 0);
}