#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ name; int /*<<< orphan*/  obj; struct TYPE_7__* next; } ;
struct TYPE_6__ {scalar_t__ z_loadfltr; scalar_t__ strtab; } ;
typedef  int /*<<< orphan*/  RtldLockState ;
typedef  TYPE_1__ Obj_Entry ;
typedef  TYPE_2__ Needed_Entry ;

/* Variables and functions */
 int RTLD_LAZY ; 
 int RTLD_LOCAL ; 
 int RTLD_NOW ; 
 int /*<<< orphan*/  dlopen_object (scalar_t__,int,TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ld_loadfltr ; 

__attribute__((used)) static void
load_filtee1(Obj_Entry *obj, Needed_Entry *needed, int flags,
    RtldLockState *lockstate)
{

    for (; needed != NULL; needed = needed->next) {
	needed->obj = dlopen_object(obj->strtab + needed->name, -1, obj,
	  flags, ((ld_loadfltr || obj->z_loadfltr) ? RTLD_NOW : RTLD_LAZY) |
	  RTLD_LOCAL, lockstate);
    }
}