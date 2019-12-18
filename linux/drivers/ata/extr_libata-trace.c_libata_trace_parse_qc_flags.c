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
 unsigned int ATA_QCFLAG_ACTIVE ; 
 unsigned int ATA_QCFLAG_CLEAR_EXCL ; 
 unsigned int ATA_QCFLAG_DMAMAP ; 
 unsigned int ATA_QCFLAG_EH_SCHEDULED ; 
 unsigned int ATA_QCFLAG_FAILED ; 
 unsigned int ATA_QCFLAG_IO ; 
 unsigned int ATA_QCFLAG_QUIET ; 
 unsigned int ATA_QCFLAG_RESULT_TF ; 
 unsigned int ATA_QCFLAG_RETRY ; 
 unsigned int ATA_QCFLAG_SENSE_VALID ; 
 char* trace_seq_buffer_ptr (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,...) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,char) ; 

const char *
libata_trace_parse_qc_flags(struct trace_seq *p, unsigned int qc_flags)
{
	const char *ret = trace_seq_buffer_ptr(p);

	trace_seq_printf(p, "%x", qc_flags);
	if (qc_flags) {
		trace_seq_printf(p, "{ ");
		if (qc_flags & ATA_QCFLAG_ACTIVE)
			trace_seq_printf(p, "ACTIVE ");
		if (qc_flags & ATA_QCFLAG_DMAMAP)
			trace_seq_printf(p, "DMAMAP ");
		if (qc_flags & ATA_QCFLAG_IO)
			trace_seq_printf(p, "IO ");
		if (qc_flags & ATA_QCFLAG_RESULT_TF)
			trace_seq_printf(p, "RESULT_TF ");
		if (qc_flags & ATA_QCFLAG_CLEAR_EXCL)
			trace_seq_printf(p, "CLEAR_EXCL ");
		if (qc_flags & ATA_QCFLAG_QUIET)
			trace_seq_printf(p, "QUIET ");
		if (qc_flags & ATA_QCFLAG_RETRY)
			trace_seq_printf(p, "RETRY ");
		if (qc_flags & ATA_QCFLAG_FAILED)
			trace_seq_printf(p, "FAILED ");
		if (qc_flags & ATA_QCFLAG_SENSE_VALID)
			trace_seq_printf(p, "SENSE_VALID ");
		if (qc_flags & ATA_QCFLAG_EH_SCHEDULED)
			trace_seq_printf(p, "EH_SCHEDULED ");
		trace_seq_putc(p, '}');
	}
	trace_seq_putc(p, 0);

	return ret;
}