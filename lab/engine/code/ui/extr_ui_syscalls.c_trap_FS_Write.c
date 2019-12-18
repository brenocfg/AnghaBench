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
 int /*<<< orphan*/  UI_FS_WRITE ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,void const*,int,int /*<<< orphan*/ ) ; 

void trap_FS_Write( const void *buffer, int len, fileHandle_t f ) {
	syscall( UI_FS_WRITE, buffer, len, f );
}