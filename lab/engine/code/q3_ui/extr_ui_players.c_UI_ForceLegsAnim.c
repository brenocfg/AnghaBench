#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int legsAnim; int /*<<< orphan*/  legsAnimationTimer; } ;
typedef  TYPE_1__ playerInfo_t ;

/* Variables and functions */
 int ANIM_TOGGLEBIT ; 
 int LEGS_JUMP ; 
 int /*<<< orphan*/  UI_TIMER_JUMP ; 

__attribute__((used)) static void UI_ForceLegsAnim( playerInfo_t *pi, int anim ) {
	pi->legsAnim = ( ( pi->legsAnim & ANIM_TOGGLEBIT ) ^ ANIM_TOGGLEBIT ) | anim;

	if ( anim == LEGS_JUMP ) {
		pi->legsAnimationTimer = UI_TIMER_JUMP;
	}
}