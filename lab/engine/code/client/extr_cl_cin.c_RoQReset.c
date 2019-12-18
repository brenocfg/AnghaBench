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
struct TYPE_4__ {int /*<<< orphan*/  file; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; int /*<<< orphan*/  iFile; int /*<<< orphan*/  fileName; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMV_LOOPED ; 
 int /*<<< orphan*/  FS_FCloseFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_FOpenFileRead (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_Read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RoQ_init () ; 
 TYPE_2__ cin ; 
 TYPE_1__* cinTable ; 
 size_t currentHandle ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static void RoQReset( void ) {
	
	if (currentHandle < 0) return;

	FS_FCloseFile( cinTable[currentHandle].iFile );
	FS_FOpenFileRead (cinTable[currentHandle].fileName, &cinTable[currentHandle].iFile, qtrue);
	// let the background thread start reading ahead
	FS_Read (cin.file, 16, cinTable[currentHandle].iFile);
	RoQ_init();
	cinTable[currentHandle].status = FMV_LOOPED;
}