#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  byte ;
struct TYPE_6__ {int playonwalls; int CIN_WIDTH; int drawX; int CIN_HEIGHT; int drawY; void* dirty; int /*<<< orphan*/ * buf; } ;
struct TYPE_5__ {scalar_t__ integer; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* UploadCinematic ) (int,int,int,int,int /*<<< orphan*/ *,int,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CIN_ResampleCinematic (int,int*) ; 
 int* Hunk_AllocateTempMemory (int) ; 
 int /*<<< orphan*/  Hunk_FreeTempMemory (int*) ; 
 int MAX_VIDEO_HANDLES ; 
 TYPE_3__* cinTable ; 
 TYPE_2__* cl_inGameVideo ; 
 void* qfalse ; 
 void* qtrue ; 
 TYPE_1__ re ; 
 int /*<<< orphan*/  stub1 (int,int,int,int,int /*<<< orphan*/ *,int,void*) ; 
 int /*<<< orphan*/  stub2 (int,int,int,int,int /*<<< orphan*/ *,int,void*) ; 

void CIN_UploadCinematic(int handle) {
	if (handle >= 0 && handle < MAX_VIDEO_HANDLES) {
		if (!cinTable[handle].buf) {
			return;
		}
		if (cinTable[handle].playonwalls <= 0 && cinTable[handle].dirty) {
			if (cinTable[handle].playonwalls == 0) {
				cinTable[handle].playonwalls = -1;
			} else {
				if (cinTable[handle].playonwalls == -1) {
					cinTable[handle].playonwalls = -2;
				} else {
					cinTable[handle].dirty = qfalse;
				}
			}
		}

		// Resample the video if needed
		if (cinTable[handle].dirty && (cinTable[handle].CIN_WIDTH != cinTable[handle].drawX || cinTable[handle].CIN_HEIGHT != cinTable[handle].drawY))  {
			int *buf2;

			buf2 = Hunk_AllocateTempMemory( 256*256*4 );

			CIN_ResampleCinematic(handle, buf2);

			re.UploadCinematic( cinTable[handle].CIN_WIDTH, cinTable[handle].CIN_HEIGHT, 256, 256, (byte *)buf2, handle, qtrue);
			cinTable[handle].dirty = qfalse;
			Hunk_FreeTempMemory(buf2);
		} else {
			// Upload video at normal resolution
			re.UploadCinematic( cinTable[handle].CIN_WIDTH, cinTable[handle].CIN_HEIGHT, cinTable[handle].drawX, cinTable[handle].drawY,
					cinTable[handle].buf, handle, cinTable[handle].dirty);
			cinTable[handle].dirty = qfalse;
		}

		if (cl_inGameVideo->integer == 0 && cinTable[handle].playonwalls == 1) {
			cinTable[handle].playonwalls--;
		}
		else if (cl_inGameVideo->integer != 0 && cinTable[handle].playonwalls != 1) {
			cinTable[handle].playonwalls = 1;
		}
	}
}