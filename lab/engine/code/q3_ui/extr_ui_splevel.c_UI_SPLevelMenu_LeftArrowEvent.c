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
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  UI_SPLevelMenu_SetMenuItems () ; 
 scalar_t__ minTier ; 
 scalar_t__ selectedArenaSet ; 

__attribute__((used)) static void UI_SPLevelMenu_LeftArrowEvent( void* ptr, int notification ) {
	if (notification != QM_ACTIVATED) {
		return;
	}

	if ( selectedArenaSet == minTier ) {
		return;
	}

	selectedArenaSet--;
	UI_SPLevelMenu_SetMenuItems();
}