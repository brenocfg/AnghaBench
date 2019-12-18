#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int vi_width; int vi_height; int vi_depth; int vi_planes; } ;
struct TYPE_8__ {int va_line_width; int va_window_size; TYPE_1__ va_info; scalar_t__ va_window; } ;
typedef  TYPE_2__ video_adapter_t ;
typedef  int uint8_t ;
struct TYPE_9__ {int zlen; int width; int height; int bpsl; int* zdata; int /*<<< orphan*/  palette; } ;

/* Variables and functions */
 int MAXSCANLINE ; 
 int /*<<< orphan*/  bcopy (int*,int*,int) ; 
 int /*<<< orphan*/  bzero (int*,int) ; 
 TYPE_5__ pcx_info ; 
 int /*<<< orphan*/  vidd_load_palette (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vidd_set_win_org (TYPE_2__*,int) ; 

__attribute__((used)) static int
pcx_draw(video_adapter_t *adp)
{
	uint8_t *vidmem;
	int swidth, sheight, sbpsl, sdepth, splanes;
	int banksize, origin;
	int c, i, j, pos, scan, x, y;
	uint8_t line[MAXSCANLINE];

	if (pcx_info.zlen < 1)
		return (1);

	vidd_load_palette(adp, pcx_info.palette);

	vidmem = (uint8_t *)adp->va_window;
	swidth = adp->va_info.vi_width;
	sheight = adp->va_info.vi_height;
	sbpsl = adp->va_line_width;
	sdepth = adp->va_info.vi_depth;
	splanes = adp->va_info.vi_planes;
	banksize = adp->va_window_size;

	for (origin = 0; origin < sheight*sbpsl; origin += banksize) {
		vidd_set_win_org(adp, origin);
		bzero(vidmem, banksize);
	}

	x = (swidth - pcx_info.width) / 2;
	y = (sheight - pcx_info.height) / 2;
	origin = 0;
	pos = y * sbpsl + x;
	while (pos > banksize) {
		pos -= banksize;
		origin += banksize;
	}
	vidd_set_win_org(adp, origin);

	for (scan = i = 0; scan < pcx_info.height; ++scan, ++y, pos += sbpsl) {
		for (j = 0; j < pcx_info.bpsl && i < pcx_info.zlen; ++i) {
			if ((pcx_info.zdata[i] & 0xc0) == 0xc0) {
				c = pcx_info.zdata[i++] & 0x3f;
				if (i >= pcx_info.zlen)
					return (1);
			} else {
				c = 1;
			}
			if (j + c > pcx_info.bpsl)
				return (1);
			while (c--)
				line[j++] = pcx_info.zdata[i];
		}

		if (pos > banksize) {
			origin += banksize;
			pos -= banksize;
			vidd_set_win_org(adp, origin);
		}

		if (pos + pcx_info.width > banksize) {
			/* scanline crosses bank boundary */
			j = banksize - pos;
			bcopy(line, vidmem + pos, j);
			origin += banksize;
			pos -= banksize;
			vidd_set_win_org(adp, origin);
			bcopy(line + j, vidmem, pcx_info.width - j);
		} else {
			bcopy(line, vidmem + pos, pcx_info.width);
		}
	}

	return (0);
}