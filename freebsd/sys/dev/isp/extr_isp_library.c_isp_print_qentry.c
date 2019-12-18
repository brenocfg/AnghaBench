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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  ispsoftc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_LOGALL ; 
 int /*<<< orphan*/  ISP_SNPRINTF (char*,int,char*,...) ; 
 int QENTRY_LEN ; 
 int TBA ; 
 int /*<<< orphan*/  isp_prt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,...) ; 

void
isp_print_qentry(ispsoftc_t *isp, const char *msg, int idx, void *arg)
{
	char buf[TBA];
	int amt, i, j;
	uint8_t *ptr = arg;

	isp_prt(isp, ISP_LOGALL, "%s index %d=>", msg, idx);
	for (buf[0] = 0, amt = i = 0; i < 4; i++) {
		buf[0] = 0;
		ISP_SNPRINTF(buf, TBA, "  ");
		for (j = 0; j < (QENTRY_LEN >> 2); j++) {
			ISP_SNPRINTF(buf, TBA, "%s %02x", buf, ptr[amt++] & 0xff);
		}
		isp_prt(isp, ISP_LOGALL, "%s", buf);
	}
}