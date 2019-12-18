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
typedef  enum tftp_error { ____Placeholder_tftp_error } tftp_error ;

/* Variables and functions */
#define  tftp_access_violation 136 
#define  tftp_disk_full 135 
#define  tftp_file_already_exists 134 
#define  tftp_file_not_found 133 
#define  tftp_illegal_operation 132 
#define  tftp_no_such_user 131 
#define  tftp_option_negotiation 130 
#define  tftp_undef 129 
#define  tftp_unknown_transfer_id 128 

char *show_error (enum tftp_error e) {
  switch (e) {
    case tftp_undef: return "Not defined";
    case tftp_file_not_found: return "File not found";
    case tftp_access_violation: return "Access violation";
    case tftp_disk_full: return "Disk full or allocation exceeded";
    case tftp_illegal_operation: return "Illegal TFTP operation";
    case tftp_unknown_transfer_id: return "Unknown transfer ID";
    case tftp_file_already_exists: return "File already exists";
    case tftp_no_such_user: return "No such user";
    case tftp_option_negotiation: return "Option negotiation error";
  }
  return "Bad error code";
}