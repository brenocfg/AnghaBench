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
 int /*<<< orphan*/  GDB_SIGNAL_TRAP ; 
 int /*<<< orphan*/  append_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_char (char) ; 
 int /*<<< orphan*/  append_integer (int) ; 
 int /*<<< orphan*/  append_string (char*) ; 
 int /*<<< orphan*/  finish_packet () ; 
 int /*<<< orphan*/  start_packet () ; 
 int stopped_vcpu ; 

__attribute__((used)) static void
report_stop(void)
{

	start_packet();
	if (stopped_vcpu == -1)
		append_char('S');
	else
		append_char('T');
	append_byte(GDB_SIGNAL_TRAP);
	if (stopped_vcpu != -1) {
		append_string("thread:");
		append_integer(stopped_vcpu + 1);
		append_char(';');
	}
	stopped_vcpu = -1;
	finish_packet();
}