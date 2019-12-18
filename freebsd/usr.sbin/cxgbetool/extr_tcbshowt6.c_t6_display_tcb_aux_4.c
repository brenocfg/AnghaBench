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
 int /*<<< orphan*/  val64 (char*) ; 

void t6_display_tcb_aux_4 (_TCBVAR *tvp, int aux)
{


  
  PR("TLS:  offset: 0x%6.6x, len:0x%6.6x, flags: 0x%4.4x\n",
	      val("rx_tls_buf_offset"),val("rx_tls_buf_len"),
	      val("rx_tls_flags"));
  PR("      seq: 0x%llx \n",val64("rx_tls_seq")); 
  PR("      tag: 0x%8.8x, key:0x%8.8x\n",
	      val("rx_tls_buf_tag"),val("rx_tls_key_tag"));




}