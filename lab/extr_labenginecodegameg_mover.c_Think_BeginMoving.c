#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  trType; int /*<<< orphan*/  trTime; } ;
struct TYPE_7__ {TYPE_1__ pos; } ;
struct TYPE_8__ {TYPE_2__ s; } ;
typedef  TYPE_3__ gentity_t ;
struct TYPE_9__ {int /*<<< orphan*/  time; } ;

/* Variables and functions */
 int /*<<< orphan*/  TR_LINEAR_STOP ; 
 TYPE_4__ level ; 

void Think_BeginMoving( gentity_t *ent ) {
	ent->s.pos.trTime = level.time;
	ent->s.pos.trType = TR_LINEAR_STOP;
}