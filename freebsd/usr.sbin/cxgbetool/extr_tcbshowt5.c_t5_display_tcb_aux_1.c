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
 int /*<<< orphan*/  PR (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  val (char*) ; 

void t5_display_tcb_aux_1 (_TCBVAR *tvp, int aux)
{


  
  PR("    aux1_slush0: 0x%x aux1_slush1 0x%x\n",
	      val("aux1_slush0"), val("aux1_slush1"));
  PR("    pdu_hdr_len %u\n",val("pdu_hdr_len"));
  


}