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
typedef  int uint16_t ;

/* Variables and functions */
 int PRLI_WD3_CONFIRMED_COMPLETION_ALLOWED ; 
 int PRLI_WD3_DATA_OVERLAY_ALLOWED ; 
 int PRLI_WD3_ENHANCED_DISCOVERY ; 
 int PRLI_WD3_INITIATOR_FUNCTION ; 
 int PRLI_WD3_READ_FCP_XFER_RDY_DISABLED ; 
 int PRLI_WD3_REC_SUPPORT ; 
 int PRLI_WD3_RETRY ; 
 int PRLI_WD3_TARGET_FUNCTION ; 
 int PRLI_WD3_TASK_RETRY_IDENTIFICATION_REQUESTED ; 
 int PRLI_WD3_WRITE_FCP_XFER_RDY_DISABLED ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 

void
isp_gen_role_str(char *buf, size_t len, uint16_t p3)
{
	int nd = 0;
	buf[0] = '(';
	buf[1] = 0;
	if (p3 & PRLI_WD3_ENHANCED_DISCOVERY) {
		nd++;
		strlcat(buf, "EDisc", len);
	}
	if (p3 & PRLI_WD3_REC_SUPPORT) {
		if (nd++) {
			strlcat(buf, ",", len);
		}
		strlcat(buf, "REC", len);
	}
	if (p3 & PRLI_WD3_TASK_RETRY_IDENTIFICATION_REQUESTED) {
		if (nd++) {
			strlcat(buf, ",", len);
		}
		strlcat(buf, "RetryID", len);
	}
	if (p3 & PRLI_WD3_RETRY) {
		if (nd++) {
			strlcat(buf, ",", len);
		}
		strlcat(buf, "Retry", len);
	}
	if (p3 & PRLI_WD3_CONFIRMED_COMPLETION_ALLOWED) {
		if (nd++) {
			strlcat(buf, ",", len);
		}
		strlcat(buf, "CNFRM", len);
	}
	if (p3 & PRLI_WD3_DATA_OVERLAY_ALLOWED) {
		if (nd++) {
			strlcat(buf, ",", len);
		}
		strlcat(buf, "DOver", len);
	}
	if (p3 & PRLI_WD3_INITIATOR_FUNCTION) {
		if (nd++) {
			strlcat(buf, ",", len);
		}
		strlcat(buf, "INI", len);
	}
	if (p3 & PRLI_WD3_TARGET_FUNCTION) {
		if (nd++) {
			strlcat(buf, ",", len);
		}
		strlcat(buf, "TGT", len);
	}
	if (p3 & PRLI_WD3_READ_FCP_XFER_RDY_DISABLED) {
		if (nd++) {
			strlcat(buf, ",", len);
		}
		strlcat(buf, "RdXfrDis", len);
	}
	if (p3 & PRLI_WD3_WRITE_FCP_XFER_RDY_DISABLED) {
		if (nd++) {
			strlcat(buf, ",", len);
		}
		strlcat(buf, "XfrDis", len);
	}
	strlcat(buf, ")", len);
}