#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vesa_mode {int v_modeattr; int v_bpp; int v_planes; int v_width; int v_linbpscanline; int v_bpscanline; } ;
struct TYPE_2__ {int v_version; } ;

/* Variables and functions */
 int V_MODEGRAPHICS ; 
 int V_MODELFB ; 
 TYPE_1__* vesa_adp_info ; 

__attribute__((used)) static int
vesa_get_bpscanline(struct vesa_mode *vmode)
{
	int bpsl;

	if ((vmode->v_modeattr & V_MODEGRAPHICS) != 0) {
		/* Find the minimum length. */
		switch (vmode->v_bpp / vmode->v_planes) {
		case 1:
			bpsl = vmode->v_width / 8;
			break;
		case 2:
			bpsl = vmode->v_width / 4;
			break;
		case 4:
			bpsl = vmode->v_width / 2;
			break;
		default:
			bpsl = vmode->v_width * ((vmode->v_bpp + 7) / 8);
			bpsl /= vmode->v_planes;
			break;
		}

		/* Use VBE 3.0 information if it looks sane. */
		if ((vmode->v_modeattr & V_MODELFB) != 0 &&
		    vesa_adp_info->v_version >= 0x0300 &&
		    vmode->v_linbpscanline > bpsl)
			return (vmode->v_linbpscanline);

		/* Return the minimum if the mode table looks absurd. */
		if (vmode->v_bpscanline < bpsl)
			return (bpsl);
	}

	return (vmode->v_bpscanline);
}