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
 int rpc_read_packet_from_file (char*) ; 
 int rpcc_log_error (int) ; 

int debug_parse_error_packet_from_file (char *s) {
  int r = rpc_read_packet_from_file (s);
  if (r < 0) {
    return r;
  }
  return rpcc_log_error (4 * r);
}