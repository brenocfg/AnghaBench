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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  cpuset_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CLR (int,int /*<<< orphan*/ *) ; 
 scalar_t__ CPU_EMPTY (int /*<<< orphan*/ *) ; 
 int CPU_FFS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  append_asciihex (char*) ; 
 int /*<<< orphan*/  append_char (char) ; 
 int /*<<< orphan*/  append_integer (int) ; 
 int /*<<< orphan*/  append_string (char*) ; 
 int /*<<< orphan*/  check_features (char const*,size_t) ; 
 scalar_t__ command_equals (char const*,size_t,char*) ; 
 int cur_vcpu ; 
 int /*<<< orphan*/  finish_packet () ; 
 int parse_threadid (char const*,size_t) ; 
 int /*<<< orphan*/  send_empty_response () ; 
 int /*<<< orphan*/  send_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  start_packet () ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  vcpus_active ; 

__attribute__((used)) static void
gdb_query(const uint8_t *data, size_t len)
{

	/*
	 * TODO:
	 * - qSearch
	 */
	if (command_equals(data, len, "qAttached")) {
		start_packet();
		append_char('1');
		finish_packet();
	} else if (command_equals(data, len, "qC")) {
		start_packet();
		append_string("QC");
		append_integer(cur_vcpu + 1);
		finish_packet();
	} else if (command_equals(data, len, "qfThreadInfo")) {
		cpuset_t mask;
		bool first;
		int vcpu;

		if (CPU_EMPTY(&vcpus_active)) {
			send_error(EINVAL);
			return;
		}
		mask = vcpus_active;
		start_packet();
		append_char('m');
		first = true;
		while (!CPU_EMPTY(&mask)) {
			vcpu = CPU_FFS(&mask) - 1;
			CPU_CLR(vcpu, &mask);
			if (first)
				first = false;
			else
				append_char(',');
			append_integer(vcpu + 1);
		}
		finish_packet();
	} else if (command_equals(data, len, "qsThreadInfo")) {
		start_packet();
		append_char('l');
		finish_packet();
	} else if (command_equals(data, len, "qSupported")) {
		data += strlen("qSupported");
		len -= strlen("qSupported");
		check_features(data, len);
	} else if (command_equals(data, len, "qThreadExtraInfo")) {
		char buf[16];
		int tid;

		data += strlen("qThreadExtraInfo");
		len -= strlen("qThreadExtraInfo");
		if (*data != ',') {
			send_error(EINVAL);
			return;
		}
		tid = parse_threadid(data + 1, len - 1);
		if (tid <= 0 || !CPU_ISSET(tid - 1, &vcpus_active)) {
			send_error(EINVAL);
			return;
		}

		snprintf(buf, sizeof(buf), "vCPU %d", tid - 1);
		start_packet();
		append_asciihex(buf);
		finish_packet();
	} else
		send_empty_response();
}