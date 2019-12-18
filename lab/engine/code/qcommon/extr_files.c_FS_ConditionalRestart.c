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
typedef  scalar_t__ qboolean ;
struct TYPE_4__ {scalar_t__* string; } ;
struct TYPE_3__ {scalar_t__ modified; scalar_t__* string; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_GameRestart (int,scalar_t__) ; 
 scalar_t__ FS_FilenameCompare (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  FS_ReorderPurePaks () ; 
 int /*<<< orphan*/  FS_Restart (int) ; 
 TYPE_2__* com_basegame ; 
 int fs_checksumFeed ; 
 TYPE_1__* fs_gamedirvar ; 
 scalar_t__ fs_numServerPaks ; 
 int /*<<< orphan*/  fs_reordered ; 
 scalar_t__* lastValidGame ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 

qboolean FS_ConditionalRestart(int checksumFeed, qboolean disconnect)
{
	if(fs_gamedirvar->modified)
	{
		if(FS_FilenameCompare(lastValidGame, fs_gamedirvar->string) &&
				(*lastValidGame || FS_FilenameCompare(fs_gamedirvar->string, com_basegame->string)) &&
				(*fs_gamedirvar->string || FS_FilenameCompare(lastValidGame, com_basegame->string)))
		{
			Com_GameRestart(checksumFeed, disconnect);
			return qtrue;
		}
		else
			fs_gamedirvar->modified = qfalse;
	}

	if(checksumFeed != fs_checksumFeed)
		FS_Restart(checksumFeed);
	else if(fs_numServerPaks && !fs_reordered)
		FS_ReorderPurePaks();

	return qfalse;
}