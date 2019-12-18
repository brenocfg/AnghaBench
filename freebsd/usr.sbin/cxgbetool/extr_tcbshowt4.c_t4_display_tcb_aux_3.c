#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  _TCBVAR ;

/* Variables and functions */
 int /*<<< orphan*/  PR (char*,...) ; 
 int val (char*) ; 

void t4_display_tcb_aux_3 (_TCBVAR *tvp, int aux)
{




  PR("  aux3_slush: 0x%x, unused: buf0 0x%x, buf1: 0x%x, main: 0x%x\n",
	      val("aux3_slush"),val("ddp_buf0_unused"),val("ddp_buf1_unused"),
	      val("ddp_main_unused"));
	      




  PR("  DDP: DDPOFF  ActBuf  IndOut  WaitFrag  Rx2Tx  BufInf\n");
  PR("         %u       %u       %u        %u        %u      %u\n",
	      val("ddp_off"),val("ddp_active_buf"),val("ddp_indicate_out"),
	      val("ddp_wait_frag"),val("ddp_rx2tx"),val("ddp_buf_inf")
	     );


	      


  PR("        Ind  PshfEn PushDis Flush NoInvalidate\n");
  PR("   Buf0: %u      %u       %u    %u       %u\n",
	      val("ddp_buf0_indicate"),
	      val("ddp_pshf_enable_0"), val("ddp_push_disable_0"),
	      val("ddp_buf0_flush"),  val("ddp_psh_no_invalidate0")
	       );
  PR("   Buf1: %u      %u       %u    %u       %u\n",
	      val("ddp_buf1_indicate"),
	      val("ddp_pshf_enable_1"), val("ddp_push_disable_1"),
	      val("ddp_buf1_flush"),  val("ddp_psh_no_invalidate1")
	       );










  PR("        Valid  Offset   Length    Tag\n");
  PR("   Buf0:  %u    0x%6.6x 0x%6.6x  0x%8.8x",
	      val("ddp_buf0_valid"),val("rx_ddp_buf0_offset"), 
	      val("rx_ddp_buf0_len"),val("rx_ddp_buf0_tag") 


	       );
  if      (0==val("ddp_off") && 1==val("ddp_buf0_valid") && 0==val("ddp_active_buf")) {
    PR("   (Active)\n");
  } else {
    PR(" (Inactive)\n");
  }


  PR("   Buf1:  %u    0x%6.6x 0x%6.6x  0x%8.8x",
	      val("ddp_buf1_valid"),val("rx_ddp_buf1_offset"), 
	      val("rx_ddp_buf1_len"),val("rx_ddp_buf1_tag") 


	       );


  if      (0==val("ddp_off") && 1==val("ddp_buf1_valid") && 1==val("ddp_active_buf")) {
    PR("   (Active)\n");
  } else {
    PR(" (Inactive)\n");
  }






  if    (1==val("ddp_off")) {
    PR("   DDP is off (which also disables indicate)\n");
  } else if (1==val("ddp_buf0_valid") && 0==val("ddp_active_buf")) {
    PR("   Data being DDP'ed to buf 0, ");
    PR("which has %u - %u = %u bytes of space left\n",
		val("rx_ddp_buf0_len"),val("rx_ddp_buf0_offset"),
		val("rx_ddp_buf0_len")-val("rx_ddp_buf0_offset")
	       );
    if (1==val("ddp_buf1_valid")) {
      PR("   And buf1, which is also valid, has %u - %u = %u bytes of space left\n",
		  val("rx_ddp_buf1_len"),val("rx_ddp_buf1_offset"),
		  val("rx_ddp_buf1_len")-val("rx_ddp_buf1_offset")
		 );
    }
  } else if (1==val("ddp_buf1_valid") && 1==val("ddp_active_buf")) {
    PR("   Data being DDP'ed to buf 1, ");
    PR("which has %u - %u = %u bytes of space left\n",
		val("rx_ddp_buf1_len"),val("rx_ddp_buf1_offset"),
		val("rx_ddp_buf1_len")-val("rx_ddp_buf1_offset")
	       );
    if (1==val("ddp_buf0_valid")) {
      PR("   And buf0, which is also valid, has %u - %u = %u bytes of space left\n",
		  val("rx_ddp_buf0_len"),val("rx_ddp_buf0_offset"),
		  val("rx_ddp_buf0_len")-val("rx_ddp_buf0_offset")
		 );
    }
  } else if (0==val("ddp_buf0_valid") && 1==val("ddp_buf1_valid") && 0==val("ddp_active_buf")) {
    PR("   !!! Invalid DDP buf 1 valid, but buf 0 active.\n");
  } else if (1==val("ddp_buf0_valid") && 0==val("ddp_buf1_valid") && 1==val("ddp_active_buf")) {
    PR("   !!! Invalid DDP buf 0 valid, but buf 1 active.\n");
  } else {
    PR("   DDP is enabled, but no buffers are active && valid.\n");




    if (0==val("ddp_indicate_out")) {
      if (0==val("ddp_buf0_indicate") && 0==val("ddp_buf1_indicate")) {
	PR("   0 length Indicate buffers ");
	if (0==val("rx_hdr_offset")) {
	  PR("will cause new data to be held in PMRX.\n");	
	} else {
	  PR("is causing %u bytes to be held in PMRX\n",
		      val("rx_hdr_offset"));
	}
      } else {
	PR("   Data being indicated to host\n");	  
      }
    } else if (1==val("ddp_indicate_out")) {
      PR("   Indicate is off, which ");
      if (0==val("rx_hdr_offset")) {
	PR("will cause new data to be held in PMRX.\n");	
      } else {
	PR("is causing %u bytes to be held in PMRX\n",
		    val("rx_hdr_offset"));
      }	
    }
  }




}