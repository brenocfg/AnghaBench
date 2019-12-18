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

/* Variables and functions */
 int /*<<< orphan*/  CPU_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_FFS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  GDB_SIGNAL_TRAP ; 
 int /*<<< orphan*/  append_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_char (char) ; 
 int cur_vcpu ; 
 int /*<<< orphan*/  finish_packet () ; 
 int /*<<< orphan*/  gdb_query (char const*,size_t) ; 
 int /*<<< orphan*/  gdb_read_mem (char const*,size_t) ; 
 int /*<<< orphan*/  gdb_read_regs () ; 
 int /*<<< orphan*/  gdb_resume_vcpus () ; 
 int /*<<< orphan*/  gdb_step_vcpu (int) ; 
 int /*<<< orphan*/  gdb_write_mem (char const*,size_t) ; 
 int parse_threadid (char const*,size_t) ; 
 int /*<<< orphan*/  send_empty_response () ; 
 int /*<<< orphan*/  send_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_ok () ; 
 int /*<<< orphan*/  start_packet () ; 
 int /*<<< orphan*/  vcpus_active ; 

__attribute__((used)) static void
handle_command(const uint8_t *data, size_t len)
{

	/* Reject packets with a sequence-id. */
	if (len >= 3 && data[0] >= '0' && data[0] <= '9' &&
	    data[0] >= '0' && data[0] <= '9' && data[2] == ':') {
		send_empty_response();
		return;
	}

	switch (*data) {
	case 'c':
		if (len != 1) {
			send_error(EINVAL);
			break;
		}

		/* Don't send a reply until a stop occurs. */
		gdb_resume_vcpus();
		break;
	case 'D':
		send_ok();

		/* TODO: Resume any stopped CPUs. */
		break;
	case 'g': {
		gdb_read_regs();
		break;
	}
	case 'H': {
		int tid;

		if (data[1] != 'g' && data[1] != 'c') {
			send_error(EINVAL);
			break;
		}
		tid = parse_threadid(data + 2, len - 2);
		if (tid == -2) {
			send_error(EINVAL);
			break;
		}

		if (CPU_EMPTY(&vcpus_active)) {
			send_error(EINVAL);
			break;
		}
		if (tid == -1 || tid == 0)
			cur_vcpu = CPU_FFS(&vcpus_active) - 1;
		else if (CPU_ISSET(tid - 1, &vcpus_active))
			cur_vcpu = tid - 1;
		else {
			send_error(EINVAL);
			break;
		}
		send_ok();
		break;
	}
	case 'm':
		gdb_read_mem(data, len);
		break;
	case 'M':
		gdb_write_mem(data, len);
		break;
	case 'T': {
		int tid;

		tid = parse_threadid(data + 1, len - 1);
		if (tid <= 0 || !CPU_ISSET(tid - 1, &vcpus_active)) {
			send_error(EINVAL);
			return;
		}
		send_ok();
		break;
	}
	case 'q':
		gdb_query(data, len);
		break;
	case 's':
		if (len != 1) {
			send_error(EINVAL);
			break;
		}

		/* Don't send a reply until a stop occurs. */
		if (!gdb_step_vcpu(cur_vcpu)) {
			send_error(EOPNOTSUPP);
			break;
		}
		break;
	case '?':
		/* XXX: Only if stopped? */
		/* For now, just report that we are always stopped. */
		start_packet();
		append_char('S');
		append_byte(GDB_SIGNAL_TRAP);
		finish_packet();
		break;
	case 'G': /* TODO */
	case 'v':
		/* Handle 'vCont' */
		/* 'vCtrlC' */
	case 'p': /* TODO */
	case 'P': /* TODO */
	case 'Q': /* TODO */
	case 't': /* TODO */
	case 'X': /* TODO */
	case 'z': /* TODO */
	case 'Z': /* TODO */
	default:
		send_empty_response();
	}
}