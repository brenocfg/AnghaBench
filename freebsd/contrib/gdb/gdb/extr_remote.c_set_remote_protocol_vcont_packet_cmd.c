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
 int /*<<< orphan*/  remote_protocol_vcont ; 
 int /*<<< orphan*/  update_packet_config (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
set_remote_protocol_vcont_packet_cmd (char *args, int from_tty,
				      struct cmd_list_element *c)
{
  update_packet_config (&remote_protocol_vcont);
}