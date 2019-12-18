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
struct TYPE_3__ {int comp; unsigned int val; int /*<<< orphan*/  name; int /*<<< orphan*/  rawval; } ;
typedef  TYPE_1__ _TCBVAR ;

/* Variables and functions */
#define  COMP_LEN 133 
#define  COMP_NONE 132 
#define  COMP_PTR 131 
#define  COMP_RCV_NXT 130 
#define  COMP_TX_MAX 129 
#define  COMP_ULP 128 
 unsigned int PM_MODE_DDP ; 
 unsigned int PM_MODE_IANDP ; 
 unsigned int PM_MODE_RDDP ; 
 int /*<<< orphan*/  tcb_code_err_exit (char*,int) ; 
 int /*<<< orphan*/  tcb_startswith_nc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tcb_strmatch_nc (int /*<<< orphan*/ ,char*) ; 

void
decompress_val(_TCBVAR *tvp,unsigned ulp_type,unsigned tx_max, 
	       unsigned rcv_nxt,unsigned rx_frag0_start_idx_raw)
{
  unsigned rawval=(unsigned) tvp->rawval;

  switch(tvp->comp) {
  case COMP_NONE: tvp->val=rawval;  break;
  case COMP_ULP:  tvp->val=rawval;  break;
  case COMP_TX_MAX: 
    tvp->val=(tx_max - rawval) & 0xFFFFFFFF;
    break;
  case COMP_RCV_NXT:
    if (tcb_startswith_nc(tvp->name,"rx_frag")) {
      unsigned fragx=0;
      if (!tcb_strmatch_nc(tvp->name,"rx_frag0_start_idx_raw")) 
	fragx=rawval;
      tvp->val=(rcv_nxt+rx_frag0_start_idx_raw+fragx) & 0xFFFFFFFF;
    } else {
      tvp->val=(rcv_nxt - rawval) & 0xFFFFFFFF;
    }
    break;
  case COMP_PTR: tvp->val=rawval;  break;
  case COMP_LEN: 
    {
      tvp->val=rawval;  
      if (PM_MODE_RDDP==ulp_type ||  PM_MODE_DDP==ulp_type ||
	  PM_MODE_IANDP==ulp_type) {
	/* TP does this internally.  Not sure if I should show the
	 *  unaltered value or the raw value.  For now I
	 *  will diplay the raw value.  For now I've added the code
	 *  mainly to stop windows compiler from warning about ulp_type
	 *  being an unreferenced parameter.
	 */
	tvp->val=0;
	tvp->val=rawval;  /* comment this out to display altered value */
      }
    }
    break;
  default:
    tcb_code_err_exit("decompress_val, bad switch: %d",tvp->comp);
    break;
  }



}