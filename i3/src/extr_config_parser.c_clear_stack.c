#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ num; int /*<<< orphan*/ * str; } ;
struct TYPE_4__ {scalar_t__ type; TYPE_1__ val; int /*<<< orphan*/ * identifier; } ;

/* Variables and functions */
 scalar_t__ STACK_STR ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_2__* stack ; 

__attribute__((used)) static void clear_stack(void) {
    for (int c = 0; c < 10; c++) {
        if (stack[c].type == STACK_STR)
            free(stack[c].val.str);
        stack[c].identifier = NULL;
        stack[c].val.str = NULL;
        stack[c].val.num = 0;
    }
}