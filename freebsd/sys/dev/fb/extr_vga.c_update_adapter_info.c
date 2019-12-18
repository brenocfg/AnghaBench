#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int vi_flags; scalar_t__ vi_mem_model; int vi_width; int vi_depth; int vi_planes; int /*<<< orphan*/  vi_buffer_size; int /*<<< orphan*/  vi_buffer; int /*<<< orphan*/  vi_window_gran; int /*<<< orphan*/  vi_window_size; int /*<<< orphan*/  vi_window; } ;
typedef  TYPE_2__ video_info_t ;
struct TYPE_7__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_9__ {int va_flags; int va_line_width; int /*<<< orphan*/  va_info; TYPE_1__ va_disp_start; int /*<<< orphan*/  va_buffer_size; int /*<<< orphan*/  va_buffer; scalar_t__ va_window_orig; int /*<<< orphan*/  va_window_gran; int /*<<< orphan*/  va_window_size; int /*<<< orphan*/  va_window; int /*<<< orphan*/  va_crtc_addr; } ;
typedef  TYPE_3__ video_adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIOS_PADDRTOVADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COLOR_CRTC ; 
 int /*<<< orphan*/  MONO_CRTC ; 
 int V_ADP_COLOR ; 
 int V_ADP_CWIDTH9 ; 
 int V_INFO_COLOR ; 
 int V_INFO_CWIDTH9 ; 
 int V_INFO_GRAPHICS ; 
 scalar_t__ V_INFO_MM_VGAX ; 
 int /*<<< orphan*/  bcopy (TYPE_2__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
update_adapter_info(video_adapter_t *adp, video_info_t *info)
{
    adp->va_flags &= ~V_ADP_COLOR;
    adp->va_flags |= 
	(info->vi_flags & V_INFO_COLOR) ? V_ADP_COLOR : 0;
    adp->va_crtc_addr =
	(adp->va_flags & V_ADP_COLOR) ? COLOR_CRTC : MONO_CRTC;
    adp->va_window = BIOS_PADDRTOVADDR(info->vi_window);
    adp->va_window_size = info->vi_window_size;
    adp->va_window_gran = info->vi_window_gran;
    adp->va_window_orig = 0;
    /* XXX */
    adp->va_buffer = info->vi_buffer;
    adp->va_buffer_size = info->vi_buffer_size;
    adp->va_flags &= ~V_ADP_CWIDTH9;
    if (info->vi_flags & V_INFO_CWIDTH9)
	adp->va_flags |= V_ADP_CWIDTH9;
    if (info->vi_mem_model == V_INFO_MM_VGAX) {
	adp->va_line_width = info->vi_width/2;
    } else if (info->vi_flags & V_INFO_GRAPHICS) {
	switch (info->vi_depth/info->vi_planes) {
	case 1:
	    adp->va_line_width = info->vi_width/8;
	    break;
	case 2:
	    adp->va_line_width = info->vi_width/4;
	    break;
	case 4:
	    adp->va_line_width = info->vi_width/2;
	    break;
	case 8:
	default: /* shouldn't happen */
	    adp->va_line_width = info->vi_width;
	    break;
	}
    } else {
	adp->va_line_width = info->vi_width;
    }
    adp->va_disp_start.x = 0;
    adp->va_disp_start.y = 0;
    bcopy(info, &adp->va_info, sizeof(adp->va_info));
}