#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int val; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ _TCBVAR ;

/* Variables and functions */
 unsigned int PM_MODE_DTLS ; 
 unsigned int PM_MODE_FCOE ; 
 unsigned int PM_MODE_IANDP ; 
 unsigned int PM_MODE_RDDP ; 
 unsigned int PM_MODE_TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  decompress_val (TYPE_1__*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int g_tN ; 
 int /*<<< orphan*/  get_tcb_field (TYPE_1__*,unsigned char*) ; 
 scalar_t__ tcb_strmatch_nc (char*,int /*<<< orphan*/ *) ; 

unsigned
parse_tcb( _TCBVAR *base_tvp, unsigned char *buf)
{   /* parse the TCB */
  _TCBVAR *tvp=base_tvp;
  unsigned ulp_type;
  int aux=1;  /* assume TOE or iSCSI */
  unsigned tx_max=0, rcv_nxt=0, rx_frag0_start_idx_raw=0;
  int got_tx_max=0, got_rcv_nxt=0, got_rx_frag0_start_idx_raw=0;


  /* parse the TCB */
  while (tvp->name!=NULL) {
    get_tcb_field(tvp,buf);
    if (!got_tx_max && tcb_strmatch_nc("tx_max",tvp->name)) {
      tx_max=tvp->val;
      got_tx_max=1;
    }
    if (!got_rcv_nxt && tcb_strmatch_nc("rcv_nxt",tvp->name)) {
      rcv_nxt=tvp->val;
      got_rcv_nxt=1;
    }
    if (!got_rx_frag0_start_idx_raw && 
	tcb_strmatch_nc("rx_frag0_start_idx_raw",tvp->name)) {
      rx_frag0_start_idx_raw=tvp->val;
      got_rx_frag0_start_idx_raw=1;
    }
    tvp+=1;
  }

  tvp=base_tvp;
  ulp_type=tvp->val;  /* ULP type is always first variable in TCB */
  if (PM_MODE_IANDP==ulp_type || PM_MODE_FCOE==ulp_type) aux=3;
  else if (PM_MODE_RDDP==ulp_type) aux=2;
  else if (6==g_tN && (PM_MODE_TLS==ulp_type || PM_MODE_DTLS==ulp_type)) aux=4;
  else aux=1;

  assert(got_tx_max && got_rcv_nxt && got_rx_frag0_start_idx_raw);
 
  /* decompress the compressed values */
  tvp=base_tvp;
  while (tvp->name!=NULL) {
    decompress_val(tvp,ulp_type,tx_max,rcv_nxt,rx_frag0_start_idx_raw);
    tvp+=1;
  }

  return aux;
}