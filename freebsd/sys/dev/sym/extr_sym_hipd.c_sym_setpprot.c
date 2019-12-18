#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_char ;
typedef  TYPE_4__* tcb_p ;
typedef  TYPE_5__* hcb_p ;
typedef  TYPE_6__* ccb_p ;
struct TYPE_17__ {size_t target; } ;
struct TYPE_16__ {TYPE_4__* target; } ;
struct TYPE_13__ {void* options; void* offset; void* period; void* width; } ;
struct TYPE_12__ {void* options; void* offset; void* period; void* width; } ;
struct TYPE_14__ {TYPE_2__ current; TYPE_1__ goal; } ;
struct TYPE_15__ {TYPE_3__ tinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYM_SPI_VALID_PPR ; 
 int /*<<< orphan*/  sym_settrans (TYPE_5__*,TYPE_6__*,void*,void*,void*,void*,void*,void*) ; 
 int /*<<< orphan*/  sym_xpt_async_transfer_neg (TYPE_5__*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sym_setpprot(hcb_p np, ccb_p cp, u_char dt, u_char ofs,
			 u_char per, u_char wide, u_char div, u_char fak)
{
	tcb_p tp = &np->target[cp->target];

	sym_settrans(np, cp, dt, ofs, per, wide, div, fak);

	/*
	 *  Tell the SCSI layer about the new transfer parameters.
	 */
	tp->tinfo.goal.width	= tp->tinfo.current.width  = wide;
	tp->tinfo.goal.period	= tp->tinfo.current.period = per;
	tp->tinfo.goal.offset	= tp->tinfo.current.offset = ofs;
	tp->tinfo.goal.options	= tp->tinfo.current.options = dt;

	sym_xpt_async_transfer_neg(np, cp->target, SYM_SPI_VALID_PPR);
}