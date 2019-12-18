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
struct TYPE_4__ {int /*<<< orphan*/  bcr2; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCR2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCR2_INVRXC0 ; 
 int /*<<< orphan*/  BCR2_INVRXC1 ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ct_set_invrxc (ct_chan_t *c, int on)
{
	if (on) c->board->bcr2 |=  (c->num ? BCR2_INVRXC1 : BCR2_INVRXC0);
	else	c->board->bcr2 &= ~(c->num ? BCR2_INVRXC1 : BCR2_INVRXC0);
	outb (BCR2(c->board->port), c->board->bcr2);
}