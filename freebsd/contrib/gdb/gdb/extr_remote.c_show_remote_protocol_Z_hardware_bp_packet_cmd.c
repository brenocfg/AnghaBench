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
struct cmd_list_element {int dummy; } ;

/* Variables and functions */
 size_t Z_PACKET_HARDWARE_BP ; 
 int /*<<< orphan*/ * remote_protocol_Z ; 
 int /*<<< orphan*/  show_packet_config_cmd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
show_remote_protocol_Z_hardware_bp_packet_cmd (char *args, int from_tty,
					       struct cmd_list_element *c)
{
  show_packet_config_cmd (&remote_protocol_Z[Z_PACKET_HARDWARE_BP]);
}