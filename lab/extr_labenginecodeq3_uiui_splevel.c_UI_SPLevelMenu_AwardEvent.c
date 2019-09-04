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
struct TYPE_3__ {int id; } ;
typedef  TYPE_1__ menucommon_s ;
struct TYPE_4__ {int /*<<< orphan*/ * awardSounds; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_ANNOUNCER ; 
 int ID_AWARD1 ; 
 int QM_ACTIVATED ; 
 TYPE_2__ levelMenuInfo ; 
 int /*<<< orphan*/  trap_S_StartLocalSound (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void UI_SPLevelMenu_AwardEvent( void* ptr, int notification ) {
	int		n;

	if (notification != QM_ACTIVATED) {
		return;
	}

	n = ((menucommon_s*)ptr)->id - ID_AWARD1;
	trap_S_StartLocalSound( levelMenuInfo.awardSounds[n], CHAN_ANNOUNCER );
}