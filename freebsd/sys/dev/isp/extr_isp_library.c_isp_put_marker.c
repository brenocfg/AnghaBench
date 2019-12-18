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
struct TYPE_4__ {int /*<<< orphan*/ * mrk_reserved1; int /*<<< orphan*/  mrk_lun; int /*<<< orphan*/  mrk_flags; int /*<<< orphan*/  mrk_modifier; int /*<<< orphan*/  mrk_target; int /*<<< orphan*/  mrk_reserved0; int /*<<< orphan*/  mrk_handle; int /*<<< orphan*/  mrk_header; } ;
typedef  TYPE_1__ isp_marker_t ;

/* Variables and functions */
 int ASIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ISP_IS_SBUS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isp_put_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
isp_put_marker(ispsoftc_t *isp, isp_marker_t *src, isp_marker_t *dst)
{
	int i;
	isp_put_hdr(isp, &src->mrk_header, &dst->mrk_header);
	ISP_IOXPUT_32(isp, src->mrk_handle, &dst->mrk_handle);
	if (ISP_IS_SBUS(isp)) {
		ISP_IOXPUT_8(isp, src->mrk_reserved0, &dst->mrk_target);
		ISP_IOXPUT_8(isp, src->mrk_target, &dst->mrk_reserved0);
	} else {
		ISP_IOXPUT_8(isp, src->mrk_reserved0, &dst->mrk_reserved0);
		ISP_IOXPUT_8(isp, src->mrk_target, &dst->mrk_target);
	}
	ISP_IOXPUT_16(isp, src->mrk_modifier, &dst->mrk_modifier);
	ISP_IOXPUT_16(isp, src->mrk_flags, &dst->mrk_flags);
	ISP_IOXPUT_16(isp, src->mrk_lun, &dst->mrk_lun);
	for (i = 0; i < ASIZE(src->mrk_reserved1); i++) {
		ISP_IOXPUT_8(isp, src->mrk_reserved1[i], &dst->mrk_reserved1[i]);
	}
}