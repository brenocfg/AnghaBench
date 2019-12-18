#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int msec; } ;
struct TYPE_8__ {TYPE_1__ pc; } ;
struct TYPE_7__ {int (* Milliseconds ) () ;} ;
struct TYPE_6__ {int /*<<< orphan*/  numIndexes; } ;

/* Variables and functions */
 void* PADP (void const*,int) ; 
 void* RB_CapShadowMap (void const*) ; 
 void* RB_ClearDepth (void const*) ; 
 void* RB_ColorMask (void const*) ; 
 void* RB_DrawBuffer (void const*) ; 
 void* RB_DrawSurfs (void const*) ; 
 int /*<<< orphan*/  RB_EndSurface () ; 
 void* RB_ExportCubemaps (void const*) ; 
 void* RB_PostProcess (void const*) ; 
 void* RB_SetColor (void const*) ; 
 void* RB_StretchPic (void const*) ; 
 void* RB_SwapBuffers (void const*) ; 
 void* RB_TakeScreenshotCmd (void const*) ; 
 void* RB_TakeVideoFrameCmd (void const*) ; 
#define  RC_CAPSHADOWMAP 140 
#define  RC_CLEARDEPTH 139 
#define  RC_COLORMASK 138 
#define  RC_DRAW_BUFFER 137 
#define  RC_DRAW_SURFS 136 
#define  RC_END_OF_LIST 135 
#define  RC_EXPORT_CUBEMAPS 134 
#define  RC_POSTPROCESS 133 
#define  RC_SCREENSHOT 132 
#define  RC_SET_COLOR 131 
#define  RC_STRETCH_PIC 130 
#define  RC_SWAP_BUFFERS 129 
#define  RC_VIDEOFRAME 128 
 TYPE_4__ backEnd ; 
 TYPE_3__ ri ; 
 int stub1 () ; 
 int stub2 () ; 
 TYPE_2__ tess ; 

void RB_ExecuteRenderCommands( const void *data ) {
	int		t1, t2;

	t1 = ri.Milliseconds ();

	while ( 1 ) {
		data = PADP(data, sizeof(void *));

		switch ( *(const int *)data ) {
		case RC_SET_COLOR:
			data = RB_SetColor( data );
			break;
		case RC_STRETCH_PIC:
			data = RB_StretchPic( data );
			break;
		case RC_DRAW_SURFS:
			data = RB_DrawSurfs( data );
			break;
		case RC_DRAW_BUFFER:
			data = RB_DrawBuffer( data );
			break;
		case RC_SWAP_BUFFERS:
			data = RB_SwapBuffers( data );
			break;
		case RC_SCREENSHOT:
			data = RB_TakeScreenshotCmd( data );
			break;
		case RC_VIDEOFRAME:
			data = RB_TakeVideoFrameCmd( data );
			break;
		case RC_COLORMASK:
			data = RB_ColorMask(data);
			break;
		case RC_CLEARDEPTH:
			data = RB_ClearDepth(data);
			break;
		case RC_CAPSHADOWMAP:
			data = RB_CapShadowMap(data);
			break;
		case RC_POSTPROCESS:
			data = RB_PostProcess(data);
			break;
		case RC_EXPORT_CUBEMAPS:
			data = RB_ExportCubemaps(data);
			break;
		case RC_END_OF_LIST:
		default:
			// finish any 2D drawing if needed
			if(tess.numIndexes)
				RB_EndSurface();

			// stop rendering
			t2 = ri.Milliseconds ();
			backEnd.pc.msec = t2 - t1;
			return;
		}
	}

}