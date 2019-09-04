#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_2__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int /*<<< orphan*/  FS_BuildOSPath (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  FS_FileInPathExists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_gamedir ; 
 TYPE_1__* fs_homepath ; 

qboolean FS_FileExists(const char *file)
{
	return FS_FileInPathExists(FS_BuildOSPath(fs_homepath->string, fs_gamedir, file));
}