#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  fileHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  UI_FS_SEEK ; 
 int syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,int) ; 

int trap_FS_Seek( fileHandle_t f, long offset, int origin ) {
	return syscall( UI_FS_SEEK, f, offset, origin );
}