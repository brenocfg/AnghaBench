#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_18__ ;

/* Type definitions */
struct TYPE_22__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ video_display_start_t ;
struct TYPE_23__ {int /*<<< orphan*/ * transparent; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; int /*<<< orphan*/  count; int /*<<< orphan*/  index; } ;
typedef  TYPE_3__ video_color_palette_t ;
struct TYPE_21__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_24__ {int va_line_width; int /*<<< orphan*/  va_mode; TYPE_1__ va_disp_start; } ;
typedef  TYPE_4__ video_adapter_t ;
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct fbcmap {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; int /*<<< orphan*/  count; int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_20__ {int (* ioctl ) (TYPE_4__*,int,scalar_t__) ;} ;

/* Variables and functions */
 int ENODEV ; 
#define  FBIOGETCMAP 134 
#define  FBIOPUTCMAP 133 
#define  FBIO_GETPALETTE 132 
#define  FBIO_SETDISPSTART 131 
#define  FBIO_SETLINEWIDTH 130 
#define  FBIO_SETPALETTE 129 
#define  FBIO_SETWINORG 128 
 int /*<<< orphan*/  VESA_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_palette (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_18__* prevvidsw ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  set_palette (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_4__*,int,scalar_t__) ; 
 int stub2 (TYPE_4__*,int,scalar_t__) ; 
 int stub3 (TYPE_4__*,int,scalar_t__) ; 
 int stub4 (TYPE_4__*,int,scalar_t__) ; 
 int stub5 (TYPE_4__*,int,scalar_t__) ; 
 int stub6 (TYPE_4__*,int,scalar_t__) ; 
 int stub7 (TYPE_4__*,int,scalar_t__) ; 
 int stub8 (TYPE_4__*,int,scalar_t__) ; 
 int stub9 (TYPE_4__*,int,scalar_t__) ; 
 TYPE_4__* vesa_adp ; 
 int /*<<< orphan*/  vesa_bios_set_line_length (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vesa_bios_set_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vesa_set_origin (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vesa_ioctl(video_adapter_t *adp, u_long cmd, caddr_t arg)
{
	int bytes;

	if (adp != vesa_adp)
		return ((*prevvidsw->ioctl)(adp, cmd, arg));

	switch (cmd) {
	case FBIO_SETWINORG:	/* set frame buffer window origin */
		if (!VESA_MODE(adp->va_mode))
			return (*prevvidsw->ioctl)(adp, cmd, arg);
		return (vesa_set_origin(adp, *(off_t *)arg) ? ENODEV : 0);

	case FBIO_SETDISPSTART:	/* set display start address */
		if (!VESA_MODE(adp->va_mode))
			return ((*prevvidsw->ioctl)(adp, cmd, arg));
		if (vesa_bios_set_start(((video_display_start_t *)arg)->x,
					((video_display_start_t *)arg)->y))
			return (ENODEV);
		adp->va_disp_start.x = ((video_display_start_t *)arg)->x;
		adp->va_disp_start.y = ((video_display_start_t *)arg)->y;
		return (0);

	case FBIO_SETLINEWIDTH:	/* set line length in pixel */
		if (!VESA_MODE(adp->va_mode))
			return ((*prevvidsw->ioctl)(adp, cmd, arg));
		if (vesa_bios_set_line_length(*(u_int *)arg, &bytes, NULL))
			return (ENODEV);
		adp->va_line_width = bytes;
#if VESA_DEBUG > 1
		printf("new line width:%d\n", adp->va_line_width);
#endif
		return (0);

	case FBIO_GETPALETTE:	/* get color palette */
		if (get_palette(adp, ((video_color_palette_t *)arg)->index,
				((video_color_palette_t *)arg)->count,
				((video_color_palette_t *)arg)->red,
				((video_color_palette_t *)arg)->green,
				((video_color_palette_t *)arg)->blue,
				((video_color_palette_t *)arg)->transparent))
			return ((*prevvidsw->ioctl)(adp, cmd, arg));
		return (0);


	case FBIO_SETPALETTE:	/* set color palette */
		if (set_palette(adp, ((video_color_palette_t *)arg)->index,
				((video_color_palette_t *)arg)->count,
				((video_color_palette_t *)arg)->red,
				((video_color_palette_t *)arg)->green,
				((video_color_palette_t *)arg)->blue,
				((video_color_palette_t *)arg)->transparent))
			return ((*prevvidsw->ioctl)(adp, cmd, arg));
		return (0);

	case FBIOGETCMAP:	/* get color palette */
		if (get_palette(adp, ((struct fbcmap *)arg)->index,
				((struct fbcmap *)arg)->count,
				((struct fbcmap *)arg)->red,
				((struct fbcmap *)arg)->green,
				((struct fbcmap *)arg)->blue, NULL))
			return ((*prevvidsw->ioctl)(adp, cmd, arg));
		return (0);

	case FBIOPUTCMAP:	/* set color palette */
		if (set_palette(adp, ((struct fbcmap *)arg)->index,
				((struct fbcmap *)arg)->count,
				((struct fbcmap *)arg)->red,
				((struct fbcmap *)arg)->green,
				((struct fbcmap *)arg)->blue, NULL))
			return ((*prevvidsw->ioctl)(adp, cmd, arg));
		return (0);

	default:
		return ((*prevvidsw->ioctl)(adp, cmd, arg));
	}
}