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
typedef  void* item_p ;
struct TYPE_2__ {int /*<<< orphan*/  nd_vnet; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 TYPE_1__* NGI_NODE (void*) ; 
 int /*<<< orphan*/  ng_snd_item (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ng_callout_trampoline(void *arg)
{
	item_p item = arg;

	CURVNET_SET(NGI_NODE(item)->nd_vnet);
	ng_snd_item(item, 0);
	CURVNET_RESTORE();
}