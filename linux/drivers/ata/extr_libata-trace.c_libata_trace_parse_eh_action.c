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

/* Variables and functions */
 unsigned int ATA_EH_ENABLE_LINK ; 
 unsigned int ATA_EH_HARDRESET ; 
 unsigned int ATA_EH_PARK ; 
 unsigned int ATA_EH_REVALIDATE ; 
 unsigned int ATA_EH_SOFTRESET ; 
 char* trace_seq_buffer_ptr (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,...) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,char) ; 

const char *
libata_trace_parse_eh_action(struct trace_seq *p, unsigned int eh_action)
{
	const char *ret = trace_seq_buffer_ptr(p);

	trace_seq_printf(p, "%x", eh_action);
	if (eh_action) {
		trace_seq_printf(p, "{ ");
		if (eh_action & ATA_EH_REVALIDATE)
			trace_seq_printf(p, "REVALIDATE ");
		if (eh_action & (ATA_EH_SOFTRESET | ATA_EH_HARDRESET))
			trace_seq_printf(p, "RESET ");
		else if (eh_action & ATA_EH_SOFTRESET)
			trace_seq_printf(p, "SOFTRESET ");
		else if (eh_action & ATA_EH_HARDRESET)
			trace_seq_printf(p, "HARDRESET ");
		if (eh_action & ATA_EH_ENABLE_LINK)
			trace_seq_printf(p, "ENABLE_LINK ");
		if (eh_action & ATA_EH_PARK)
			trace_seq_printf(p, "PARK ");
		trace_seq_putc(p, '}');
	}
	trace_seq_putc(p, 0);

	return ret;
}