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
struct TYPE_3__ {scalar_t__ dest_port; } ;
typedef  TYPE_1__ tftp_packet_t ;

/* Variables and functions */
 scalar_t__ CLIENT ; 
 scalar_t__ port ; 
 int /*<<< orphan*/  recv_wrq_packets ; 
 int tftp_store_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tftp_undef ; 
 scalar_t__ working_mode ; 

__attribute__((used)) static int process_wrq (tftp_packet_t *p) {
  recv_wrq_packets++;
  if (p->dest_port != port) {
    return tftp_store_error (tftp_undef, "Write request packet wasn't sent to the TFTP port");
  }
  if (working_mode == CLIENT) {
    return tftp_store_error (tftp_undef, "Write request packet was sent to client");
  }
  return tftp_store_error (tftp_undef, "Not implemented");
}