#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  baud; int /*<<< orphan*/  mode; int /*<<< orphan*/  gopt; int /*<<< orphan*/  hopt; int /*<<< orphan*/  opt; } ;
typedef  TYPE_1__ ct_chan_t ;
struct TYPE_6__ {TYPE_1__* chan; int /*<<< orphan*/  opt; } ;
typedef  TYPE_2__ ct_board_t ;

/* Variables and functions */
 int NCHAN ; 
 int /*<<< orphan*/  ct_baud ; 
 int /*<<< orphan*/  ct_board_opt_dflt ; 
 int /*<<< orphan*/  ct_chan_mode ; 
 int /*<<< orphan*/  ct_chan_opt_dflt ; 
 int /*<<< orphan*/  ct_opt_g703_dflt ; 
 int /*<<< orphan*/  ct_opt_hdlc_dflt ; 
 int /*<<< orphan*/  ct_reinit_chan (TYPE_1__*) ; 

void ct_reinit_board (ct_board_t *b)
{
	ct_chan_t *c;

	b->opt = ct_board_opt_dflt;
	for (c=b->chan; c<b->chan+NCHAN; ++c) {
		c->opt = ct_chan_opt_dflt;
		c->hopt = ct_opt_hdlc_dflt;
		c->gopt = ct_opt_g703_dflt;
		c->mode = ct_chan_mode;
		c->baud = ct_baud;

		ct_reinit_chan (c);
	}
}