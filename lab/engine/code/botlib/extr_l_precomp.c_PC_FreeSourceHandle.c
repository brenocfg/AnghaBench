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

/* Variables and functions */
 int /*<<< orphan*/  FreeSource (int /*<<< orphan*/ *) ; 
 int MAX_SOURCEFILES ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/ ** sourceFiles ; 

int PC_FreeSourceHandle(int handle)
{
	if (handle < 1 || handle >= MAX_SOURCEFILES)
		return qfalse;
	if (!sourceFiles[handle])
		return qfalse;

	FreeSource(sourceFiles[handle]);
	sourceFiles[handle] = NULL;
	return qtrue;
}