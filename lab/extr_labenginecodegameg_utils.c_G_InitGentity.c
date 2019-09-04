#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ownerNum; } ;
struct TYPE_5__ {TYPE_3__* number; } ;
struct TYPE_7__ {char* classname; TYPE_2__ r; TYPE_1__ s; int /*<<< orphan*/  inuse; } ;
typedef  TYPE_3__ gentity_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENTITYNUM_NONE ; 
 int g_entities ; 
 int /*<<< orphan*/  qtrue ; 

void G_InitGentity( gentity_t *e ) {
	e->inuse = qtrue;
	e->classname = "noclass";
	e->s.number = e - g_entities;
	e->r.ownerNum = ENTITYNUM_NONE;
}