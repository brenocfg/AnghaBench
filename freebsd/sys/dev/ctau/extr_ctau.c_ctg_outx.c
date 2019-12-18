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
typedef  int /*<<< orphan*/  port_t ;
struct TYPE_5__ {TYPE_1__* board; scalar_t__ num; } ;
typedef  TYPE_2__ ct_chan_t ;
struct TYPE_4__ {int gmd1; int /*<<< orphan*/  port; int /*<<< orphan*/  gmd0; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMD0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GMD1 (int /*<<< orphan*/ ) ; 
 int GMD1_NCS0 ; 
 int GMD1_NCS1 ; 
 unsigned char LX_WRITE ; 
 int /*<<< orphan*/  ctg_output (int /*<<< orphan*/ ,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 

void ctg_outx (ct_chan_t *c, unsigned char reg, unsigned char val)
{
	port_t port = GMD0(c->board->port);

	outb (GMD1(c->board->port), c->board->gmd1 | GMD1_NCS0 | GMD1_NCS1);
	outb (GMD1(c->board->port), c->board->gmd1 |
		(c->num ? GMD1_NCS0 : GMD1_NCS1));
	ctg_output (port, (reg << 1) | LX_WRITE, c->board->gmd0);
	ctg_output (port, val, c->board->gmd0);
	outb (GMD1(c->board->port), c->board->gmd1 | GMD1_NCS0 | GMD1_NCS1);
}