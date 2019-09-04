#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* animations; } ;
typedef  TYPE_1__ playerInfo_t ;
struct TYPE_7__ {int animationNumber; scalar_t__ frameTime; scalar_t__ animationTime; TYPE_3__* animation; } ;
typedef  TYPE_2__ lerpFrame_t ;
struct TYPE_8__ {scalar_t__ initialLerp; } ;
typedef  TYPE_3__ animation_t ;

/* Variables and functions */
 int ANIM_TOGGLEBIT ; 
 int MAX_ANIMATIONS ; 
 int /*<<< orphan*/  trap_Error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,int) ; 

__attribute__((used)) static void UI_SetLerpFrameAnimation( playerInfo_t *ci, lerpFrame_t *lf, int newAnimation ) {
	animation_t	*anim;

	lf->animationNumber = newAnimation;
	newAnimation &= ~ANIM_TOGGLEBIT;

	if ( newAnimation < 0 || newAnimation >= MAX_ANIMATIONS ) {
		trap_Error( va("Bad animation number: %i", newAnimation) );
	}

	anim = &ci->animations[ newAnimation ];

	lf->animation = anim;
	lf->animationTime = lf->frameTime + anim->initialLerp;
}