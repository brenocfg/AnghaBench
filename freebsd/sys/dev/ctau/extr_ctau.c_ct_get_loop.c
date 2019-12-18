#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int loop; } ;
struct TYPE_7__ {TYPE_1__ md2; } ;
struct TYPE_9__ {scalar_t__ mode; int lx; TYPE_2__ opt; TYPE_3__* board; scalar_t__ num; } ;
typedef  TYPE_4__ ct_chan_t ;
struct TYPE_8__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int CCR2_LLOOP ; 
 int /*<<< orphan*/  DS_CCR2 ; 
 unsigned short E1CS0 (int /*<<< orphan*/ ) ; 
 unsigned short E1CS1 (int /*<<< orphan*/ ) ; 
 int LX_LLOOP ; 
 int MD2_LLOOP ; 
 scalar_t__ M_E1 ; 
 scalar_t__ M_G703 ; 
 int cte_in (unsigned short,int /*<<< orphan*/ ) ; 

int ct_get_loop (ct_chan_t *c)
{
	if (c->mode == M_E1) {
		unsigned short p = c->num ? E1CS1 (c->board->port) :
					    E1CS0 (c->board->port);

		return cte_in (p, DS_CCR2) & CCR2_LLOOP;
	}
	if (c->mode == M_G703)
		return c->lx & LX_LLOOP;

	/* M_HDLC */
	return (c->opt.md2.loop & MD2_LLOOP) != 0;
}