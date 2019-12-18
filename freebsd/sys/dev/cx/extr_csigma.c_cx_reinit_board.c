#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int type; int /*<<< orphan*/  hopt; int /*<<< orphan*/  aopt; int /*<<< orphan*/  opt; int /*<<< orphan*/  txbaud; int /*<<< orphan*/  rxbaud; void* mode; } ;
typedef  TYPE_1__ cx_chan_t ;
struct TYPE_7__ {scalar_t__ fast; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__* chan; int /*<<< orphan*/  if8type; int /*<<< orphan*/  if0type; int /*<<< orphan*/  bcr0; TYPE_4__ opt; } ;
typedef  TYPE_2__ cx_board_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCR02X_FAST ; 
 scalar_t__ B_SIGMA_2X ; 
 void* M_ASYNC ; 
 int NCHAN ; 
#define  T_ASYNC 136 
#define  T_NONE 135 
#define  T_SYNC_RS232 134 
#define  T_SYNC_RS449 133 
#define  T_SYNC_V35 132 
#define  T_UNIV 131 
#define  T_UNIV_RS232 130 
#define  T_UNIV_RS449 129 
#define  T_UNIV_V35 128 
 TYPE_4__ board_opt_dflt ; 
 int /*<<< orphan*/  chan_opt_dflt ; 
 int /*<<< orphan*/  cx_iftype ; 
 int /*<<< orphan*/  cx_rxbaud ; 
 void* cx_sync_mode ; 
 int /*<<< orphan*/  cx_txbaud ; 
 void* cx_univ_mode ; 
 int /*<<< orphan*/  opt_async_dflt ; 
 int /*<<< orphan*/  opt_hdlc_dflt ; 

void cx_reinit_board (cx_board_t *b)
{
	cx_chan_t *c;

	b->opt = board_opt_dflt;
	if (b->type == B_SIGMA_2X) {
		b->bcr0 &= ~BCR02X_FAST;
		if (b->opt.fast)
			b->bcr0 |= BCR02X_FAST;
	} else
		b->if0type = b->if8type = cx_iftype;
	for (c=b->chan; c<b->chan+NCHAN; ++c) {
		switch (c->type) {
		default:
		case T_NONE:
			continue;
		case T_UNIV:
		case T_UNIV_RS232:
		case T_UNIV_RS449:
		case T_UNIV_V35:
			c->mode = (cx_univ_mode == M_ASYNC) ?
				M_ASYNC : cx_sync_mode;
			break;
		case T_SYNC_RS232:
		case T_SYNC_V35:
		case T_SYNC_RS449:
			c->mode = cx_sync_mode;
			break;
		case T_ASYNC:
			c->mode = M_ASYNC;
			break;
		}
		c->rxbaud = cx_rxbaud;
		c->txbaud = cx_txbaud;
		c->opt = chan_opt_dflt;
		c->aopt = opt_async_dflt;
		c->hopt = opt_hdlc_dflt;
	}
}