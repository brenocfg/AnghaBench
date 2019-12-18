#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ val; scalar_t__ rawval; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ _TCBVAR ;

/* Variables and functions */
 int /*<<< orphan*/  get_tcb_field (TYPE_1__*,unsigned char*) ; 
 scalar_t__ tcb_strmatch_nc (char*,int /*<<< orphan*/ *) ; 

void
parse_scb( _TCBVAR *base_tvp, unsigned char *buf)
{   /* parse the SCB */
  _TCBVAR *tvp=base_tvp;

  while (tvp->name!=NULL) {
    if (tcb_strmatch_nc("scb_slush",tvp->name)) {
      /* the scb_slush field is all of remaining memory */
      tvp->rawval=0;
      tvp->val=0;
    } else {
      get_tcb_field(tvp,buf);
    }
    tvp+=1;
  }
}