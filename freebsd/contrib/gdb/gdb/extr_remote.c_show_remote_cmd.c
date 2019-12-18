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
 int /*<<< orphan*/  show_remote_protocol_E_packet_cmd (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_remote_protocol_P_packet_cmd (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_remote_protocol_Z_packet_cmd (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_remote_protocol_binary_download_cmd (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_remote_protocol_e_packet_cmd (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_remote_protocol_qPart_auxv_packet_cmd (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_remote_protocol_qPart_dirty_packet_cmd (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_remote_protocol_qSymbol_packet_cmd (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_remote_protocol_vcont_packet_cmd (char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
show_remote_cmd (char *args, int from_tty)
{
  /* FIXME: cagney/2002-06-15: This function should iterate over
     remote_show_cmdlist for a list of sub commands to show.  */
  show_remote_protocol_Z_packet_cmd (args, from_tty, NULL);
  show_remote_protocol_e_packet_cmd (args, from_tty, NULL);
  show_remote_protocol_E_packet_cmd (args, from_tty, NULL);
  show_remote_protocol_P_packet_cmd (args, from_tty, NULL);
  show_remote_protocol_qSymbol_packet_cmd (args, from_tty, NULL);
  show_remote_protocol_vcont_packet_cmd (args, from_tty, NULL);
  show_remote_protocol_binary_download_cmd (args, from_tty, NULL);
  show_remote_protocol_qPart_auxv_packet_cmd (args, from_tty, NULL);
  show_remote_protocol_qPart_dirty_packet_cmd (args, from_tty, NULL);
}