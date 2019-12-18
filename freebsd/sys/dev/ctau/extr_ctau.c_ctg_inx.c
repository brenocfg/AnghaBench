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
struct TYPE_4__ {int gmd1; int gmd0; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLDR (int /*<<< orphan*/ ) ; 
 unsigned char GLDR_C0 ; 
 unsigned char GLDR_C1 ; 
 int /*<<< orphan*/  GMD0 (int /*<<< orphan*/ ) ; 
 int GMD0_SCLK ; 
 int /*<<< orphan*/  GMD1 (int /*<<< orphan*/ ) ; 
 int GMD1_NCS0 ; 
 int GMD1_NCS1 ; 
 unsigned char LX_READ ; 
 int /*<<< orphan*/  ctg_output (int /*<<< orphan*/ ,unsigned char,int) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 

unsigned char ctg_inx (ct_chan_t *c, unsigned char reg)
{
	port_t port = GMD0(c->board->port);
	port_t data = GLDR(c->board->port);
	unsigned char val = 0, mask = c->num ? GLDR_C1 : GLDR_C0;
	int i;

	outb (GMD1(c->board->port), c->board->gmd1 | GMD1_NCS0 | GMD1_NCS1);
	outb (GMD1(c->board->port), c->board->gmd1 |
		(c->num ? GMD1_NCS0 : GMD1_NCS1));
	ctg_output (port, (reg << 1) | LX_READ, c->board->gmd0);
	for (i=0; i<8; ++i) {
		outb (port, c->board->gmd0 | GMD0_SCLK);
		if (inb (data) & mask)
			val |= 1 << i;
		outb (port, c->board->gmd0);
	}
	outb (GMD1(c->board->port), c->board->gmd1 | GMD1_NCS0 | GMD1_NCS1);
	return val;
}