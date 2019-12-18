#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int* vec3_t ;
struct TYPE_5__ {int /*<<< orphan*/  ms; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_6__ {int /*<<< orphan*/  movedir; int /*<<< orphan*/  failure; } ;
typedef  TYPE_2__ bot_moveresult_t ;

/* Variables and functions */
 int /*<<< orphan*/  AngleVectors (int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MOVE_WALK ; 
 int /*<<< orphan*/  VectorCopy (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int random () ; 
 int /*<<< orphan*/  trap_BotMoveInDirection (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 

void BotRandomMove(bot_state_t *bs, bot_moveresult_t *moveresult) {
	vec3_t dir, angles;

	angles[0] = 0;
	angles[1] = random() * 360;
	angles[2] = 0;
	AngleVectors(angles, dir, NULL, NULL);

	trap_BotMoveInDirection(bs->ms, dir, 400, MOVE_WALK);

	moveresult->failure = qfalse;
	VectorCopy(dir, moveresult->movedir);
}