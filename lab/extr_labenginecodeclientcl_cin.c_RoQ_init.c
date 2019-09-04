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
struct TYPE_4__ {int* file; } ;
struct TYPE_3__ {int RoQPlayed; int roqFPS; int numQuads; int roq_id; int RoQFrameSize; int roq_flags; int /*<<< orphan*/  lastTime; int /*<<< orphan*/  startTime; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_ScaledMilliseconds () ; 
 TYPE_2__ cin ; 
 TYPE_1__* cinTable ; 
 size_t currentHandle ; 

__attribute__((used)) static void RoQ_init( void )
{
	cinTable[currentHandle].startTime = cinTable[currentHandle].lastTime = CL_ScaledMilliseconds();

	cinTable[currentHandle].RoQPlayed = 24;

/*	get frame rate */	
	cinTable[currentHandle].roqFPS	 = cin.file[ 6] + cin.file[ 7]*256;
	
	if (!cinTable[currentHandle].roqFPS) cinTable[currentHandle].roqFPS = 30;

	cinTable[currentHandle].numQuads = -1;

	cinTable[currentHandle].roq_id		= cin.file[ 8] + cin.file[ 9]*256;
	cinTable[currentHandle].RoQFrameSize	= cin.file[10] + cin.file[11]*256 + cin.file[12]*65536;
	cinTable[currentHandle].roq_flags	= cin.file[14] + cin.file[15]*256;

	if (cinTable[currentHandle].RoQFrameSize > 65536 || !cinTable[currentHandle].RoQFrameSize) { 
		return;
	}

}