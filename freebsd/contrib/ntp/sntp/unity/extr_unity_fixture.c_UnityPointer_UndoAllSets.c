#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  old_value; int /*<<< orphan*/ * pointer; } ;

/* Variables and functions */
 size_t pointer_index ; 
 TYPE_1__* pointer_store ; 

void UnityPointer_UndoAllSets(void)
{
    while (pointer_index > 0)
    {
        pointer_index--;
        *(pointer_store[pointer_index].pointer) =
        pointer_store[pointer_index].old_value;

    }
}