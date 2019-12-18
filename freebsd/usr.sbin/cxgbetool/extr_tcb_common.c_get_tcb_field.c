#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int hi; int lo; int rawval; unsigned int val; } ;
typedef  TYPE_1__ _TCBVAR ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int get_tcb_bits (unsigned char*,scalar_t__,scalar_t__) ; 

void
get_tcb_field(_TCBVAR *tvp,unsigned char *buf)
{
  assert(tvp->hi-tvp->lo+1<=64);
  assert(tvp->hi>=tvp->lo);

  tvp->rawval=get_tcb_bits(buf,tvp->lo,tvp->hi);
  /* assume no compression and 32-bit value for now */
  tvp->val=(unsigned) (tvp->rawval & 0xFFFFFFFF);  


}