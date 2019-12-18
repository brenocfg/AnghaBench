#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned long s2; } ;
struct TYPE_8__ {TYPE_2__ opt; TYPE_1__* chan; } ;
typedef  TYPE_3__ ct_board_t ;
struct TYPE_6__ {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ M_E1 ; 
 int /*<<< orphan*/  ct_setup_e1 (TYPE_3__*) ; 

int ct_set_subchan (ct_board_t *b, unsigned long ts)
{
	if (b->chan[0].mode != M_E1)
		return -1;
	b->opt.s2 = ts;
	ct_setup_e1 (b);
	return 0;
}