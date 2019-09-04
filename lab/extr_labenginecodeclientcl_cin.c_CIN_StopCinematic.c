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
typedef  scalar_t__ e_status ;
struct TYPE_4__ {scalar_t__ status; scalar_t__ alterGameState; int /*<<< orphan*/  buf; int /*<<< orphan*/  fileName; } ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ CA_CINEMATIC ; 
 int /*<<< orphan*/  Com_DPrintf (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FMV_EOF ; 
 int MAX_VIDEO_HANDLES ; 
 int /*<<< orphan*/  RoQShutdown () ; 
 TYPE_2__* cinTable ; 
 TYPE_1__ clc ; 
 size_t currentHandle ; 

e_status CIN_StopCinematic(int handle) {
	
	if (handle < 0 || handle>= MAX_VIDEO_HANDLES || cinTable[handle].status == FMV_EOF) return FMV_EOF;
	currentHandle = handle;

	Com_DPrintf("trFMV::stop(), closing %s\n", cinTable[currentHandle].fileName);

	if (!cinTable[currentHandle].buf) {
		return FMV_EOF;
	}

	if (cinTable[currentHandle].alterGameState) {
		if ( clc.state != CA_CINEMATIC ) {
			return cinTable[currentHandle].status;
		}
	}
	cinTable[currentHandle].status = FMV_EOF;
	RoQShutdown();

	return FMV_EOF;
}