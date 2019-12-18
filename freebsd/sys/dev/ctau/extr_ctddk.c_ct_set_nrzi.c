#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  encod; } ;
struct TYPE_6__ {TYPE_1__ md2; } ;
struct TYPE_7__ {TYPE_2__ opt; int /*<<< orphan*/  MD2; } ;
typedef  TYPE_3__ ct_chan_t ;

/* Variables and functions */
 int /*<<< orphan*/  MD2_ENCOD_NRZ ; 
 int /*<<< orphan*/  MD2_ENCOD_NRZI ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,unsigned char) ; 

void ct_set_nrzi (ct_chan_t *c, int on)
{
	c->opt.md2.encod = on ? MD2_ENCOD_NRZI : MD2_ENCOD_NRZ;
	outb (c->MD2, *(unsigned char*)&c->opt.md2);
}