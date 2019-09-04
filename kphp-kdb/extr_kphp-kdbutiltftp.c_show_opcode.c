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
typedef  enum tftp_opcode { ____Placeholder_tftp_opcode } tftp_opcode ;

/* Variables and functions */
#define  tftp_ack 133 
#define  tftp_data 132 
#define  tftp_error 131 
#define  tftp_oack 130 
#define  tftp_rrq 129 
#define  tftp_wrq 128 

char *show_opcode (enum tftp_opcode o) {
  switch (o) {
    case tftp_rrq: return "Read request";
    case tftp_wrq: return "Write request";
    case tftp_data: return "Data";
    case tftp_ack: return "Acknowledgement";
    case tftp_error: return "Error";
    case tftp_oack: return "Option Acknowledgement";
  }
  return NULL;
}