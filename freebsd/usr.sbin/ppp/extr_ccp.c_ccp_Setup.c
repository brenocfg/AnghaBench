#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int algorithm; int /*<<< orphan*/ * opt; int /*<<< orphan*/ * state; } ;
struct TYPE_7__ {int id; } ;
struct TYPE_8__ {TYPE_2__ hdr; } ;
struct TYPE_9__ {int algorithm; TYPE_3__ opt; int /*<<< orphan*/  state; } ;
struct TYPE_6__ {scalar_t__ open_mode; } ;
struct ccp {int his_proto; int my_proto; int reset_sent; int last_reset; scalar_t__ compin; scalar_t__ uncompin; scalar_t__ compout; scalar_t__ uncompout; scalar_t__ my_reject; scalar_t__ his_reject; TYPE_5__ out; TYPE_4__ in; TYPE_1__ fsm; } ;

/* Variables and functions */

void
ccp_Setup(struct ccp *ccp)
{
  /* Set ourselves up for a startup */
  ccp->fsm.open_mode = 0;
  ccp->his_proto = ccp->my_proto = -1;
  ccp->reset_sent = ccp->last_reset = -1;
  ccp->in.algorithm = ccp->out.algorithm = -1;
  ccp->in.state = ccp->out.state = NULL;
  ccp->in.opt.hdr.id = -1;
  ccp->out.opt = NULL;
  ccp->his_reject = ccp->my_reject = 0;
  ccp->uncompout = ccp->compout = 0;
  ccp->uncompin = ccp->compin = 0;
}