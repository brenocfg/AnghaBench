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
struct trace_seq {int dummy; } ;
struct cper_mem_err_compact {int dummy; } ;

/* Variables and functions */
 scalar_t__ cper_dimm_err_location (struct cper_mem_err_compact*,int /*<<< orphan*/ ) ; 
 scalar_t__ cper_mem_err_location (struct cper_mem_err_compact*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcd_decode_str ; 
 char* trace_seq_buffer_ptr (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,char) ; 

const char *cper_mem_err_unpack(struct trace_seq *p,
				struct cper_mem_err_compact *cmem)
{
	const char *ret = trace_seq_buffer_ptr(p);

	if (cper_mem_err_location(cmem, rcd_decode_str))
		trace_seq_printf(p, "%s", rcd_decode_str);
	if (cper_dimm_err_location(cmem, rcd_decode_str))
		trace_seq_printf(p, "%s", rcd_decode_str);
	trace_seq_putc(p, '\0');

	return ret;
}