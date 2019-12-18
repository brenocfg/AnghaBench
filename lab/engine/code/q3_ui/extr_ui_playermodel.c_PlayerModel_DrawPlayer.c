#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ y; int /*<<< orphan*/  x; } ;
struct TYPE_6__ {int height; int /*<<< orphan*/  width; TYPE_1__ generic; } ;
typedef  TYPE_2__ menubitmap_s ;
struct TYPE_8__ {int /*<<< orphan*/  playerinfo; } ;
struct TYPE_7__ {int realtime; } ;

/* Variables and functions */
 scalar_t__ LOW_MEMORY ; 
 int /*<<< orphan*/  UI_DrawPlayer (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UI_DrawProportionalString (int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_LEFT ; 
 int /*<<< orphan*/  color_blue ; 
 TYPE_4__ s_playermodel ; 
 scalar_t__ trap_MemoryRemaining () ; 
 TYPE_3__ uis ; 

__attribute__((used)) static void PlayerModel_DrawPlayer( void *self )
{
	menubitmap_s*	b;

	b = (menubitmap_s*) self;

	if( trap_MemoryRemaining() <= LOW_MEMORY ) {
		UI_DrawProportionalString( b->generic.x, b->generic.y + b->height / 2, "LOW MEMORY", UI_LEFT, color_blue );
		return;
	}

	UI_DrawPlayer( b->generic.x, b->generic.y, b->width, b->height, &s_playermodel.playerinfo, uis.realtime/2 );
}