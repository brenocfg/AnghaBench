#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  byte ;
struct TYPE_4__ {scalar_t__ status; float xpos; float ypos; float width; float height; int CIN_WIDTH; int drawX; int CIN_HEIGHT; int drawY; void* dirty; int /*<<< orphan*/ * buf; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* DrawStretchRaw ) (float,float,float,float,int,int,int /*<<< orphan*/ *,int,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CIN_ResampleCinematic (int,int*) ; 
 scalar_t__ FMV_EOF ; 
 int* Hunk_AllocateTempMemory (int) ; 
 int /*<<< orphan*/  Hunk_FreeTempMemory (int*) ; 
 int MAX_VIDEO_HANDLES ; 
 int /*<<< orphan*/  SCR_AdjustFrom640 (float*,float*,float*,float*) ; 
 TYPE_2__* cinTable ; 
 void* qfalse ; 
 void* qtrue ; 
 TYPE_1__ re ; 
 int /*<<< orphan*/  stub1 (float,float,float,float,int,int,int /*<<< orphan*/ *,int,void*) ; 
 int /*<<< orphan*/  stub2 (float,float,float,float,int,int,int /*<<< orphan*/ *,int,void*) ; 

void CIN_DrawCinematic (int handle) {
	float	x, y, w, h;
	byte	*buf;

	if (handle < 0 || handle>= MAX_VIDEO_HANDLES || cinTable[handle].status == FMV_EOF) return;

	if (!cinTable[handle].buf) {
		return;
	}

	x = cinTable[handle].xpos;
	y = cinTable[handle].ypos;
	w = cinTable[handle].width;
	h = cinTable[handle].height;
	buf = cinTable[handle].buf;
	SCR_AdjustFrom640( &x, &y, &w, &h );

	if (cinTable[handle].dirty && (cinTable[handle].CIN_WIDTH != cinTable[handle].drawX || cinTable[handle].CIN_HEIGHT != cinTable[handle].drawY)) {
		int *buf2;

		buf2 = Hunk_AllocateTempMemory( 256*256*4 );

		CIN_ResampleCinematic(handle, buf2);

		re.DrawStretchRaw( x, y, w, h, 256, 256, (byte *)buf2, handle, qtrue);
		cinTable[handle].dirty = qfalse;
		Hunk_FreeTempMemory(buf2);
		return;
	}

	re.DrawStretchRaw( x, y, w, h, cinTable[handle].drawX, cinTable[handle].drawY, buf, handle, cinTable[handle].dirty);
	cinTable[handle].dirty = qfalse;
}