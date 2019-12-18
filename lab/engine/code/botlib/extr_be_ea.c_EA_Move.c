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
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_3__ {float speed; int /*<<< orphan*/  dir; } ;
typedef  TYPE_1__ bot_input_t ;

/* Variables and functions */
 float MAX_USERMOVE ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* botinputs ; 

void EA_Move(int client, vec3_t dir, float speed)
{
	bot_input_t *bi;

	bi = &botinputs[client];

	VectorCopy(dir, bi->dir);
	//cap speed
	if (speed > MAX_USERMOVE) speed = MAX_USERMOVE;
	else if (speed < -MAX_USERMOVE) speed = -MAX_USERMOVE;
	bi->speed = speed;
}