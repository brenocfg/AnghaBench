#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; } ;
typedef  TYPE_1__ ENGINE ;

/* Variables and functions */
 int ENGINE_FLAGS_NO_REGISTER_ALL ; 
 TYPE_1__* ENGINE_get_first () ; 
 TYPE_1__* ENGINE_get_next (TYPE_1__*) ; 
 int /*<<< orphan*/  ENGINE_register_complete (TYPE_1__*) ; 

int ENGINE_register_all_complete(void)
{
    ENGINE *e;

    for (e = ENGINE_get_first(); e; e = ENGINE_get_next(e))
        if (!(e->flags & ENGINE_FLAGS_NO_REGISTER_ALL))
            ENGINE_register_complete(e);
    return 1;
}