#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ video_display_start_t ;
struct TYPE_13__ {int /*<<< orphan*/ * transparent; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; int /*<<< orphan*/  count; int /*<<< orphan*/  index; } ;
typedef  TYPE_3__ video_color_palette_t ;
struct TYPE_11__ {int vi_depth; int /*<<< orphan*/  vi_width; int /*<<< orphan*/  vi_height; } ;
struct TYPE_14__ {int /*<<< orphan*/  va_buffer_size; TYPE_1__ va_info; int /*<<< orphan*/  va_type; } ;
typedef  TYPE_4__ video_adapter_t ;
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct fbtype {int fb_depth; int fb_cmsize; int /*<<< orphan*/  fb_size; int /*<<< orphan*/  fb_width; int /*<<< orphan*/  fb_height; int /*<<< orphan*/  fb_type; } ;
struct fbcmap {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; int /*<<< orphan*/  count; int /*<<< orphan*/  index; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int ENODEV ; 
#define  FBIOGETCMAP 136 
#define  FBIOGTYPE 135 
#define  FBIOPUTCMAP 134 
#define  FBIO_GETPALETTE 133 
#define  FBIO_GETWINORG 132 
#define  FBIO_SETDISPSTART 131 
#define  FBIO_SETLINEWIDTH 130 
#define  FBIO_SETPALETTE 129 
#define  FBIO_SETWINORG 128 
 int fb_commonioctl (TYPE_4__*,int,scalar_t__) ; 
 int /*<<< orphan*/  fb_type (int /*<<< orphan*/ ) ; 
 int get_palette (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_display_start (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_line_length (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int set_palette (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vga_dev_ioctl(video_adapter_t *adp, u_long cmd, caddr_t arg)
{
    switch (cmd) {
    case FBIO_GETWINORG:	/* get frame buffer window origin */
	*(u_int *)arg = 0;
	return 0;

    case FBIO_SETWINORG:	/* set frame buffer window origin */
	return ENODEV;

    case FBIO_SETDISPSTART:	/* set display start address */
	return (set_display_start(adp, 
				  ((video_display_start_t *)arg)->x,
			  	  ((video_display_start_t *)arg)->y)
		? ENODEV : 0);

    case FBIO_SETLINEWIDTH:	/* set scan line length in pixel */
	return (set_line_length(adp, *(u_int *)arg) ? ENODEV : 0);

    case FBIO_GETPALETTE:	/* get color palette */
	return get_palette(adp, ((video_color_palette_t *)arg)->index,
			   ((video_color_palette_t *)arg)->count,
			   ((video_color_palette_t *)arg)->red,
			   ((video_color_palette_t *)arg)->green,
			   ((video_color_palette_t *)arg)->blue,
			   ((video_color_palette_t *)arg)->transparent);

    case FBIO_SETPALETTE:	/* set color palette */
	return set_palette(adp, ((video_color_palette_t *)arg)->index,
			   ((video_color_palette_t *)arg)->count,
			   ((video_color_palette_t *)arg)->red,
			   ((video_color_palette_t *)arg)->green,
			   ((video_color_palette_t *)arg)->blue,
			   ((video_color_palette_t *)arg)->transparent);

    case FBIOGTYPE:		/* get frame buffer type info. */
	((struct fbtype *)arg)->fb_type = fb_type(adp->va_type);
	((struct fbtype *)arg)->fb_height = adp->va_info.vi_height;
	((struct fbtype *)arg)->fb_width = adp->va_info.vi_width;
	((struct fbtype *)arg)->fb_depth = adp->va_info.vi_depth;
	if ((adp->va_info.vi_depth <= 1) || (adp->va_info.vi_depth > 8))
	    ((struct fbtype *)arg)->fb_cmsize = 0;
	else
	    ((struct fbtype *)arg)->fb_cmsize = 1 << adp->va_info.vi_depth;
	((struct fbtype *)arg)->fb_size = adp->va_buffer_size;
	return 0;

    case FBIOGETCMAP:		/* get color palette */
	return get_palette(adp, ((struct fbcmap *)arg)->index,
			   ((struct fbcmap *)arg)->count,
			   ((struct fbcmap *)arg)->red,
			   ((struct fbcmap *)arg)->green,
			   ((struct fbcmap *)arg)->blue, NULL);

    case FBIOPUTCMAP:		/* set color palette */
	return set_palette(adp, ((struct fbcmap *)arg)->index,
			   ((struct fbcmap *)arg)->count,
			   ((struct fbcmap *)arg)->red,
			   ((struct fbcmap *)arg)->green,
			   ((struct fbcmap *)arg)->blue, NULL);

    default:
	return fb_commonioctl(adp, cmd, arg);
    }
}