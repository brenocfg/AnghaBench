#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int fore; int back; } ;
struct TYPE_6__ {int fore; int back; } ;
struct TYPE_9__ {int* mv_ovscan; int mv_csz; int mv_rsz; int font_size; TYPE_3__ mv_norm; TYPE_1__ mv_rev; } ;
struct TYPE_7__ {int vi_flags; } ;
struct TYPE_10__ {int* active_vty; int screen_map; scalar_t__ video_mode_number; TYPE_4__ console_info; TYPE_2__ video_mode_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  KDRASTER ; 
 int /*<<< orphan*/  KDSBORDER ; 
 scalar_t__ M_VESA_BASE ; 
 int /*<<< orphan*/  PIO_SCRNMAP ; 
 int /*<<< orphan*/  VT_ACTIVATE ; 
 int V_INFO_GRAPHICS ; 
 int /*<<< orphan*/  _IO (char,scalar_t__) ; 
 TYPE_5__ cur_info ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ video_mode_changed ; 
 scalar_t__ vt4_mode ; 

__attribute__((used)) static void
revert(void)
{
	int save_errno, size[3];

	save_errno = errno;

	ioctl(0, VT_ACTIVATE, cur_info.active_vty);

	ioctl(0, KDSBORDER, cur_info.console_info.mv_ovscan);
	fprintf(stderr, "\033[=%dH", cur_info.console_info.mv_rev.fore);
	fprintf(stderr, "\033[=%dI", cur_info.console_info.mv_rev.back);

	if (vt4_mode == 0)
		ioctl(0, PIO_SCRNMAP, &cur_info.screen_map);

	if (video_mode_changed) {
		if (cur_info.video_mode_number >= M_VESA_BASE)
			ioctl(0,
			    _IO('V', cur_info.video_mode_number - M_VESA_BASE),
			    NULL);
		else
			ioctl(0, _IO('S', cur_info.video_mode_number), NULL);
		if (cur_info.video_mode_info.vi_flags & V_INFO_GRAPHICS) {
			size[0] = cur_info.console_info.mv_csz;
			size[1] = cur_info.console_info.mv_rsz;
			size[2] = cur_info.console_info.font_size;
			ioctl(0, KDRASTER, size);
		}
	}

	/* Restore some colors last since mode setting forgets some. */
	fprintf(stderr, "\033[=%dF", cur_info.console_info.mv_norm.fore);
	fprintf(stderr, "\033[=%dG", cur_info.console_info.mv_norm.back);

	errno = save_errno;
}