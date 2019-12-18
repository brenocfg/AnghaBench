#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  vi_mode; } ;
typedef  TYPE_3__ video_info_t ;
struct TYPE_17__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_4__ video_display_start_t ;
struct TYPE_15__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_18__ {int va_index; int va_type; int va_mode; int /*<<< orphan*/  va_line_width; TYPE_2__ va_disp_start; int /*<<< orphan*/  va_window_orig; int /*<<< orphan*/  va_initial_bios_mode; int /*<<< orphan*/  va_initial_mode; int /*<<< orphan*/  va_buffer_size; int /*<<< orphan*/  va_buffer; int /*<<< orphan*/  va_window_gran; int /*<<< orphan*/  va_window_size; int /*<<< orphan*/  va_window; int /*<<< orphan*/  va_mem_size; int /*<<< orphan*/  va_mem_base; int /*<<< orphan*/  va_crtc_addr; int /*<<< orphan*/  va_io_size; int /*<<< orphan*/  va_io_base; int /*<<< orphan*/  va_flags; int /*<<< orphan*/  va_unit; int /*<<< orphan*/  va_name; } ;
typedef  TYPE_5__ video_adapter_t ;
struct TYPE_14__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_19__ {int va_index; int va_type; int va_mode; TYPE_1__ va_disp_start; int /*<<< orphan*/  va_line_width; int /*<<< orphan*/  va_initial_bios_mode; int /*<<< orphan*/  va_initial_mode; int /*<<< orphan*/  va_buffer_size; void* va_unused0; int /*<<< orphan*/  va_window_orig; int /*<<< orphan*/  va_window_gran; int /*<<< orphan*/  va_window_size; void* va_window; int /*<<< orphan*/  va_mem_size; int /*<<< orphan*/  va_mem_base; int /*<<< orphan*/  va_crtc_addr; int /*<<< orphan*/  va_io_size; int /*<<< orphan*/  va_io_base; int /*<<< orphan*/  va_flags; int /*<<< orphan*/  va_unit; int /*<<< orphan*/  va_name; } ;
typedef  TYPE_6__ video_adapter_info_t ;
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_int ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int ENODEV ; 
#define  FBIOGATTR 159 
#define  FBIOGCURMAX 158 
#define  FBIOGCURPOS 157 
#define  FBIOGCURSOR 156 
#define  FBIOGETCMAP 155 
#define  FBIOGETCMAPI 154 
#define  FBIOGTYPE 153 
#define  FBIOGVIDEO 152 
#define  FBIOGXINFO 151 
#define  FBIOMONINFO 150 
#define  FBIOPUTCMAP 149 
#define  FBIOPUTCMAPI 148 
#define  FBIOSCURPOS 147 
#define  FBIOSCURSOR 146 
#define  FBIOSVIDEO 145 
#define  FBIOVERTICAL 144 
#define  FBIO_ADAPTER 143 
#define  FBIO_ADPINFO 142 
#define  FBIO_ADPTYPE 141 
#define  FBIO_BLANK 140 
#define  FBIO_FINDMODE 139 
#define  FBIO_GETDISPSTART 138 
#define  FBIO_GETLINEWIDTH 137 
#define  FBIO_GETMODE 136 
#define  FBIO_GETPALETTE 135 
#define  FBIO_GETWINORG 134 
#define  FBIO_MODEINFO 133 
#define  FBIO_SETDISPSTART 132 
#define  FBIO_SETLINEWIDTH 131 
#define  FBIO_SETMODE 130 
#define  FBIO_SETPALETTE 129 
#define  FBIO_SETWINORG 128 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imin (int /*<<< orphan*/ ,int) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int vidd_blank_display (TYPE_5__*,int) ; 
 int vidd_get_info (TYPE_5__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int vidd_query_mode (TYPE_5__*,TYPE_3__*) ; 
 int vidd_set_mode (TYPE_5__*,int) ; 
 void* vtophys (int /*<<< orphan*/ ) ; 

int
fb_commonioctl(video_adapter_t *adp, u_long cmd, caddr_t arg)
{
	int error;
	int s;

	/* assert(adp != NULL) */

	error = 0;
	s = spltty();

	switch (cmd) {

	case FBIO_ADAPTER:	/* get video adapter index */
		*(int *)arg = adp->va_index;
		break;

	case FBIO_ADPTYPE:	/* get video adapter type */
		*(int *)arg = adp->va_type;
		break;

	case FBIO_ADPINFO:	/* get video adapter info */
	        ((video_adapter_info_t *)arg)->va_index = adp->va_index;
		((video_adapter_info_t *)arg)->va_type = adp->va_type;
		bcopy(adp->va_name, ((video_adapter_info_t *)arg)->va_name,
		      imin(strlen(adp->va_name) + 1,
			   sizeof(((video_adapter_info_t *)arg)->va_name))); 
		((video_adapter_info_t *)arg)->va_unit = adp->va_unit;
		((video_adapter_info_t *)arg)->va_flags = adp->va_flags;
		((video_adapter_info_t *)arg)->va_io_base = adp->va_io_base;
		((video_adapter_info_t *)arg)->va_io_size = adp->va_io_size;
		((video_adapter_info_t *)arg)->va_crtc_addr = adp->va_crtc_addr;
		((video_adapter_info_t *)arg)->va_mem_base = adp->va_mem_base;
		((video_adapter_info_t *)arg)->va_mem_size = adp->va_mem_size;
		((video_adapter_info_t *)arg)->va_window
#if defined(__amd64__) || defined(__i386__)
			= vtophys(adp->va_window);
#else
			= adp->va_window;
#endif
		((video_adapter_info_t *)arg)->va_window_size
			= adp->va_window_size;
		((video_adapter_info_t *)arg)->va_window_gran
			= adp->va_window_gran;
		((video_adapter_info_t *)arg)->va_window_orig
			= adp->va_window_orig;
		((video_adapter_info_t *)arg)->va_unused0
#if defined(__amd64__) || defined(__i386__)
			= adp->va_buffer != 0 ? vtophys(adp->va_buffer) : 0;
#else
			= adp->va_buffer;
#endif
		((video_adapter_info_t *)arg)->va_buffer_size
			= adp->va_buffer_size;
		((video_adapter_info_t *)arg)->va_mode = adp->va_mode;
		((video_adapter_info_t *)arg)->va_initial_mode
			= adp->va_initial_mode;
		((video_adapter_info_t *)arg)->va_initial_bios_mode
			= adp->va_initial_bios_mode;
		((video_adapter_info_t *)arg)->va_line_width
			= adp->va_line_width;
		((video_adapter_info_t *)arg)->va_disp_start.x
			= adp->va_disp_start.x;
		((video_adapter_info_t *)arg)->va_disp_start.y
			= adp->va_disp_start.y;
		break;

	case FBIO_MODEINFO:	/* get mode information */
		error = vidd_get_info(adp,
		    ((video_info_t *)arg)->vi_mode,
		    (video_info_t *)arg);
		if (error)
			error = ENODEV;
		break;

	case FBIO_FINDMODE:	/* find a matching video mode */
		error = vidd_query_mode(adp, (video_info_t *)arg);
		break;

	case FBIO_GETMODE:	/* get video mode */
		*(int *)arg = adp->va_mode;
		break;

	case FBIO_SETMODE:	/* set video mode */
		error = vidd_set_mode(adp, *(int *)arg);
		if (error)
			error = ENODEV;	/* EINVAL? */
		break;

	case FBIO_GETWINORG:	/* get frame buffer window origin */
		*(u_int *)arg = adp->va_window_orig;
		break;

	case FBIO_GETDISPSTART:	/* get display start address */
		((video_display_start_t *)arg)->x = adp->va_disp_start.x;
		((video_display_start_t *)arg)->y = adp->va_disp_start.y;
		break;

	case FBIO_GETLINEWIDTH:	/* get scan line width in bytes */
		*(u_int *)arg = adp->va_line_width;
		break;

	case FBIO_BLANK:	/* blank display */
		error = vidd_blank_display(adp, *(int *)arg);
		break;

	case FBIO_GETPALETTE:	/* get color palette */
	case FBIO_SETPALETTE:	/* set color palette */
		/* XXX */

	case FBIOPUTCMAP:
	case FBIOGETCMAP:
	case FBIOPUTCMAPI:
	case FBIOGETCMAPI:
		/* XXX */

	case FBIO_SETWINORG:	/* set frame buffer window origin */
	case FBIO_SETDISPSTART:	/* set display start address */
	case FBIO_SETLINEWIDTH:	/* set scan line width in pixel */

	case FBIOGTYPE:
	case FBIOGATTR:
	case FBIOSVIDEO:
	case FBIOGVIDEO:
	case FBIOVERTICAL:
	case FBIOSCURSOR:
	case FBIOGCURSOR:
	case FBIOSCURPOS:
	case FBIOGCURPOS:
	case FBIOGCURMAX:
	case FBIOMONINFO:
	case FBIOGXINFO:

	default:
		error = ENODEV;
		break;
	}

	splx(s);
	return error;
}