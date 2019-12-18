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
typedef  enum pt_error_code { ____Placeholder_pt_error_code } pt_error_code ;

/* Variables and functions */
#define  pte_bad_config 155 
#define  pte_bad_context 154 
#define  pte_bad_cpu 153 
#define  pte_bad_file 152 
#define  pte_bad_image 151 
#define  pte_bad_insn 150 
#define  pte_bad_lock 149 
#define  pte_bad_opc 148 
#define  pte_bad_packet 147 
#define  pte_bad_query 146 
#define  pte_bad_retcomp 145 
#define  pte_bad_status_update 144 
#define  pte_eos 143 
#define  pte_event_ignored 142 
#define  pte_internal 141 
#define  pte_invalid 140 
#define  pte_ip_suppressed 139 
#define  pte_no_cbr 138 
#define  pte_no_enable 137 
#define  pte_no_time 136 
#define  pte_noip 135 
#define  pte_nomap 134 
#define  pte_nomem 133 
#define  pte_nosync 132 
#define  pte_not_supported 131 
#define  pte_ok 130 
#define  pte_overflow 129 
#define  pte_retstack_empty 128 

const char *pt_errstr(enum pt_error_code errcode)
{
	switch (errcode) {
	case pte_ok:
		return "OK";

	case pte_internal:
		return "internal error";

	case pte_invalid:
		return "invalid argument";

	case pte_nosync:
		return "decoder out of sync";

	case pte_bad_opc:
		return "unknown opcode";

	case pte_bad_packet:
		return "unknown packet";

	case pte_bad_context:
		return "unexpected packet context";

	case pte_eos:
		return "reached end of trace stream";

	case pte_bad_query:
		return "trace stream does not match query";

	case pte_nomem:
		return "out of memory";

	case pte_bad_config:
		return "bad configuration";

	case pte_noip:
		return "no ip";

	case pte_ip_suppressed:
		return "ip has been suppressed";

	case pte_nomap:
		return "no memory mapped at this address";

	case pte_bad_insn:
		return "unknown instruction";

	case pte_no_time:
		return "no timing information";

	case pte_no_cbr:
		return "no core:bus ratio";

	case pte_bad_image:
		return "bad image";

	case pte_bad_lock:
		return "locking error";

	case pte_not_supported:
		return "not supported";

	case pte_retstack_empty:
		return "compressed return without call";

	case pte_bad_retcomp:
		return "bad compressed return";

	case pte_bad_status_update:
		return "bad status update";

	case pte_no_enable:
		return "expected tracing enabled event";

	case pte_event_ignored:
		return "event ignored";

	case pte_overflow:
		return "overflow";

	case pte_bad_file:
		return "bad file";

	case pte_bad_cpu:
		return "unknown cpu";
	}

	/* Should not reach here. */
	return "internal error.";
}