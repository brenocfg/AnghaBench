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
 unsigned char ATA_BUSY ; 
 unsigned char ATA_CORR ; 
 unsigned char ATA_DF ; 
 unsigned char ATA_DRDY ; 
 unsigned char ATA_DRQ ; 
 unsigned char ATA_DSC ; 
 unsigned char ATA_ERR ; 
 unsigned char ATA_SENSE ; 
 char* trace_seq_buffer_ptr (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,char) ; 

const char *
libata_trace_parse_status(struct trace_seq *p, unsigned char status)
{
	const char *ret = trace_seq_buffer_ptr(p);

	trace_seq_printf(p, "{ ");
	if (status & ATA_BUSY)
		trace_seq_printf(p, "BUSY ");
	if (status & ATA_DRDY)
		trace_seq_printf(p, "DRDY ");
	if (status & ATA_DF)
		trace_seq_printf(p, "DF ");
	if (status & ATA_DSC)
		trace_seq_printf(p, "DSC ");
	if (status & ATA_DRQ)
		trace_seq_printf(p, "DRQ ");
	if (status & ATA_CORR)
		trace_seq_printf(p, "CORR ");
	if (status & ATA_SENSE)
		trace_seq_printf(p, "SENSE ");
	if (status & ATA_ERR)
		trace_seq_printf(p, "ERR ");
	trace_seq_putc(p, '}');
	trace_seq_putc(p, 0);

	return ret;
}