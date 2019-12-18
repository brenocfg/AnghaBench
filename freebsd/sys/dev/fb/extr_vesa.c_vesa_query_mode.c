#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ vi_mode; scalar_t__ vi_width; scalar_t__ vi_height; scalar_t__ vi_cwidth; scalar_t__ vi_cheight; scalar_t__ vi_depth; scalar_t__ vi_planes; scalar_t__ vi_flags; } ;
typedef  TYPE_1__ video_info_t ;
typedef  int /*<<< orphan*/  video_adapter_t ;
struct TYPE_7__ {scalar_t__ (* query_mode ) (int /*<<< orphan*/ *,TYPE_1__*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ EOT ; 
 TYPE_5__* prevvidsw ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * vesa_adp ; 
 TYPE_1__* vesa_vmode ; 

__attribute__((used)) static int
vesa_query_mode(video_adapter_t *adp, video_info_t *info)
{
	int i;

	if ((*prevvidsw->query_mode)(adp, info) == 0)
		return (0);
	if (adp != vesa_adp)
		return (ENODEV);

	for (i = 0; vesa_vmode[i].vi_mode != EOT; ++i) {
		if ((info->vi_width != 0)
		    && (info->vi_width != vesa_vmode[i].vi_width))
			continue;
		if ((info->vi_height != 0)
		    && (info->vi_height != vesa_vmode[i].vi_height))
			continue;
		if ((info->vi_cwidth != 0)
		    && (info->vi_cwidth != vesa_vmode[i].vi_cwidth))
			continue;
		if ((info->vi_cheight != 0)
		    && (info->vi_cheight != vesa_vmode[i].vi_cheight))
			continue;
		if ((info->vi_depth != 0)
		    && (info->vi_depth != vesa_vmode[i].vi_depth))
			continue;
		if ((info->vi_planes != 0)
		    && (info->vi_planes != vesa_vmode[i].vi_planes))
			continue;
		/* pixel format, memory model */
		if ((info->vi_flags != 0)
		    && (info->vi_flags != vesa_vmode[i].vi_flags))
			continue;
		*info = vesa_vmode[i];
		return (0);
	}
	return (ENODEV);
}