#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  encod; scalar_t__ dpll; } ;
struct TYPE_10__ {scalar_t__ llm; scalar_t__ ext1x; } ;
struct TYPE_12__ {TYPE_2__ rcor; TYPE_1__ tcor; } ;
struct TYPE_13__ {scalar_t__ type; int mode; int txbaud; int rxbaud; TYPE_3__ opt; } ;
typedef  TYPE_4__ cx_chan_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENCOD_NRZ ; 
 int M_ASYNC ; 
 int M_HDLC ; 
 scalar_t__ T_ASYNC ; 
 scalar_t__ T_SYNC_RS232 ; 
 scalar_t__ T_SYNC_RS449 ; 
 scalar_t__ T_SYNC_V35 ; 
 int /*<<< orphan*/  cx_enable_receive (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_enable_transmit (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_setup_chan (TYPE_4__*) ; 
 int /*<<< orphan*/  cx_start_chan (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cx_set_mode (cx_chan_t *c, int mode)
{
	if (mode == M_HDLC) {
		if (c->type == T_ASYNC)
			return -1;

		if (c->mode == M_HDLC)
			return 0;

		c->mode = M_HDLC;
	} else if (mode == M_ASYNC) {
		if (c->type == T_SYNC_RS232 ||
		    c->type == T_SYNC_V35   ||
		    c->type == T_SYNC_RS449)
			return -1;

		if (c->mode == M_ASYNC)
			return 0;

		c->mode = M_ASYNC;
		c->opt.tcor.ext1x = 0;
		c->opt.tcor.llm = 0;
		c->opt.rcor.dpll = 0;
		c->opt.rcor.encod = ENCOD_NRZ;
		if (! c->txbaud || ! c->rxbaud)
			c->txbaud = c->rxbaud = 9600;
	} else
		return -1;

	cx_setup_chan (c);
	cx_start_chan (c, 0, 0);
	cx_enable_receive (c, 0);
	cx_enable_transmit (c, 0);
	return 0;
}