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

/* Variables and functions */

char *
spr_tcp_state (unsigned state) 
{
  char *ret="UNKNOWN";

  if      ( 0 == state) {ret = "CLOSED";}
  else if ( 1 == state) {ret = "LISTEN";}
  else if ( 2 == state) {ret = "SYN_SENT";}
  else if ( 3 == state) {ret = "SYN_RCVD";}
  else if ( 4 == state) {ret = "ESTABLISHED";}
  else if ( 5 == state) {ret = "CLOSE_WAIT";}
  else if ( 6 == state) {ret = "FIN_WAIT_1";}
  else if ( 7 == state) {ret = "CLOSING";}
  else if ( 8 == state) {ret = "LAST_ACK";}
  else if ( 9 == state) {ret = "FIN_WAIT_2";}
  else if (10 == state) {ret = "TIME_WAIT";}
  else if (11 == state) {ret = "ESTABLISHED_RX";}
  else if (12 == state) {ret = "ESTABLISHED_TX";}
  else if (13 == state) {ret = "SYN_PEND";}
  else if (14 == state) {ret = "ESC_1_STATE";}
  else if (15 == state) {ret = "ESC_2_STATE";}

  return ret;
}