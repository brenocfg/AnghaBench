#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ng_l2cap_p ;
struct TYPE_3__ {int /*<<< orphan*/  chan_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_l2cap_free_chan (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ng_l2cap_destroy_channels(ng_l2cap_p l2cap)
{
	while (!LIST_EMPTY(&l2cap->chan_list))
		ng_l2cap_free_chan(LIST_FIRST(&l2cap->chan_list));
}