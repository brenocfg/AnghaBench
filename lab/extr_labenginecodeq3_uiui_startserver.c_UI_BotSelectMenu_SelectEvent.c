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
struct TYPE_4__ {size_t selectedmodel; int /*<<< orphan*/ * botnames; } ;
struct TYPE_3__ {int /*<<< orphan*/  newBotName; int /*<<< orphan*/  newBot; } ;

/* Variables and functions */
 size_t MAX_MODELSPERPAGE ; 
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UI_PopMenu () ; 
 TYPE_2__ botSelectInfo ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_1__ s_serveroptions ; 

__attribute__((used)) static void UI_BotSelectMenu_SelectEvent( void* ptr, int event ) {
	if( event != QM_ACTIVATED ) {
		return;
	}
	UI_PopMenu();

	s_serveroptions.newBot = qtrue;
	Q_strncpyz( s_serveroptions.newBotName, botSelectInfo.botnames[botSelectInfo.selectedmodel % MAX_MODELSPERPAGE], 16 );
}