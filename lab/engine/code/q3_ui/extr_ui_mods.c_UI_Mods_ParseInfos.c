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
struct TYPE_3__ {size_t numitems; int /*<<< orphan*/ * itemnames; } ;
struct TYPE_4__ {TYPE_1__ list; int /*<<< orphan*/  fs_gamePtr; int /*<<< orphan*/  descriptionPtr; int /*<<< orphan*/ * descriptionList; int /*<<< orphan*/ * fs_gameList; } ;

/* Variables and functions */
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__ s_mods ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void UI_Mods_ParseInfos( char *modDir, char *modDesc ) {
	s_mods.fs_gameList[s_mods.list.numitems] = s_mods.fs_gamePtr;
	Q_strncpyz( s_mods.fs_gamePtr, modDir, 16 );

	s_mods.descriptionList[s_mods.list.numitems] = s_mods.descriptionPtr;
	Q_strncpyz( s_mods.descriptionPtr, modDesc, 48 );

	s_mods.list.itemnames[s_mods.list.numitems] = s_mods.descriptionPtr;
	s_mods.descriptionPtr += strlen( s_mods.descriptionPtr ) + 1;
	s_mods.fs_gamePtr += strlen( s_mods.fs_gamePtr ) + 1;
	s_mods.list.numitems++;
}