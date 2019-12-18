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
#define  ATA_CMD_FPDMA_RECV 145 
#define  ATA_CMD_FPDMA_SEND 144 
#define  ATA_CMD_NCQ_NON_DATA 143 
#define  ATA_CMD_ZAC_MGMT_IN 142 
#define  ATA_CMD_ZAC_MGMT_OUT 141 
#define  ATA_SUBCMD_FPDMA_RECV_RD_LOG_DMA_EXT 140 
#define  ATA_SUBCMD_FPDMA_RECV_ZAC_MGMT_IN 139 
#define  ATA_SUBCMD_FPDMA_SEND_DSM 138 
#define  ATA_SUBCMD_FPDMA_SEND_WR_LOG_DMA_EXT 137 
#define  ATA_SUBCMD_NCQ_NON_DATA_ABORT_QUEUE 136 
#define  ATA_SUBCMD_NCQ_NON_DATA_SET_FEATURES 135 
#define  ATA_SUBCMD_NCQ_NON_DATA_ZAC_MGMT_OUT 134 
#define  ATA_SUBCMD_NCQ_NON_DATA_ZERO_EXT 133 
#define  ATA_SUBCMD_ZAC_MGMT_IN_REPORT_ZONES 132 
#define  ATA_SUBCMD_ZAC_MGMT_OUT_CLOSE_ZONE 131 
#define  ATA_SUBCMD_ZAC_MGMT_OUT_FINISH_ZONE 130 
#define  ATA_SUBCMD_ZAC_MGMT_OUT_OPEN_ZONE 129 
#define  ATA_SUBCMD_ZAC_MGMT_OUT_RESET_WRITE_POINTER 128 
 char* trace_seq_buffer_ptr (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,int /*<<< orphan*/ ) ; 

const char *
libata_trace_parse_subcmd(struct trace_seq *p, unsigned char cmd,
			  unsigned char feature, unsigned char hob_nsect)
{
	const char *ret = trace_seq_buffer_ptr(p);

	switch (cmd) {
	case ATA_CMD_FPDMA_RECV:
		switch (hob_nsect & 0x5f) {
		case ATA_SUBCMD_FPDMA_RECV_RD_LOG_DMA_EXT:
			trace_seq_printf(p, " READ_LOG_DMA_EXT");
			break;
		case ATA_SUBCMD_FPDMA_RECV_ZAC_MGMT_IN:
			trace_seq_printf(p, " ZAC_MGMT_IN");
			break;
		}
		break;
	case ATA_CMD_FPDMA_SEND:
		switch (hob_nsect & 0x5f) {
		case ATA_SUBCMD_FPDMA_SEND_WR_LOG_DMA_EXT:
			trace_seq_printf(p, " WRITE_LOG_DMA_EXT");
			break;
		case ATA_SUBCMD_FPDMA_SEND_DSM:
			trace_seq_printf(p, " DATASET_MANAGEMENT");
			break;
		}
		break;
	case ATA_CMD_NCQ_NON_DATA:
		switch (feature) {
		case ATA_SUBCMD_NCQ_NON_DATA_ABORT_QUEUE:
			trace_seq_printf(p, " ABORT_QUEUE");
			break;
		case ATA_SUBCMD_NCQ_NON_DATA_SET_FEATURES:
			trace_seq_printf(p, " SET_FEATURES");
			break;
		case ATA_SUBCMD_NCQ_NON_DATA_ZERO_EXT:
			trace_seq_printf(p, " ZERO_EXT");
			break;
		case ATA_SUBCMD_NCQ_NON_DATA_ZAC_MGMT_OUT:
			trace_seq_printf(p, " ZAC_MGMT_OUT");
			break;
		}
		break;
	case ATA_CMD_ZAC_MGMT_IN:
		switch (feature) {
		case ATA_SUBCMD_ZAC_MGMT_IN_REPORT_ZONES:
			trace_seq_printf(p, " REPORT_ZONES");
			break;
		}
		break;
	case ATA_CMD_ZAC_MGMT_OUT:
		switch (feature) {
		case ATA_SUBCMD_ZAC_MGMT_OUT_CLOSE_ZONE:
			trace_seq_printf(p, " CLOSE_ZONE");
			break;
		case ATA_SUBCMD_ZAC_MGMT_OUT_FINISH_ZONE:
			trace_seq_printf(p, " FINISH_ZONE");
			break;
		case ATA_SUBCMD_ZAC_MGMT_OUT_OPEN_ZONE:
			trace_seq_printf(p, " OPEN_ZONE");
			break;
		case ATA_SUBCMD_ZAC_MGMT_OUT_RESET_WRITE_POINTER:
			trace_seq_printf(p, " RESET_WRITE_POINTER");
			break;
		}
		break;
	}
	trace_seq_putc(p, 0);

	return ret;
}