#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* board; scalar_t__ num; } ;
typedef  TYPE_2__ ct_chan_t ;
struct TYPE_4__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1CS2 (int /*<<< orphan*/ ) ; 
 unsigned char E1CS2_AB ; 
 unsigned char E1CS2_SCC ; 
 int /*<<< orphan*/  E1DAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,unsigned char) ; 

void cte_out2c (ct_chan_t *c, unsigned char val)
{
	outb (E1CS2(c->board->port), E1CS2_SCC | (c->num ? 0 : E1CS2_AB));
	outb (E1DAT(c->board->port), val);
}