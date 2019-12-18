#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ispsoftc_t ;
struct TYPE_4__ {int /*<<< orphan*/  rqs_flags; int /*<<< orphan*/  rqs_seqno; int /*<<< orphan*/  rqs_entry_count; int /*<<< orphan*/  rqs_entry_type; } ;
typedef  TYPE_1__ isphdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_IOXPUT_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ISP_IS_SBUS (int /*<<< orphan*/ *) ; 

void
isp_put_hdr(ispsoftc_t *isp, isphdr_t *hpsrc, isphdr_t *hpdst)
{
	if (ISP_IS_SBUS(isp)) {
		ISP_IOXPUT_8(isp, hpsrc->rqs_entry_type, &hpdst->rqs_entry_count);
		ISP_IOXPUT_8(isp, hpsrc->rqs_entry_count, &hpdst->rqs_entry_type);
		ISP_IOXPUT_8(isp, hpsrc->rqs_seqno, &hpdst->rqs_flags);
		ISP_IOXPUT_8(isp, hpsrc->rqs_flags, &hpdst->rqs_seqno);
	} else {
		ISP_IOXPUT_8(isp, hpsrc->rqs_entry_type, &hpdst->rqs_entry_type);
		ISP_IOXPUT_8(isp, hpsrc->rqs_entry_count, &hpdst->rqs_entry_count);
		ISP_IOXPUT_8(isp, hpsrc->rqs_seqno, &hpdst->rqs_seqno);
		ISP_IOXPUT_8(isp, hpsrc->rqs_flags, &hpdst->rqs_flags);
	}
}