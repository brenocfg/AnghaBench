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
struct TYPE_3__ {char const* str; } ;
struct TYPE_4__ {TYPE_1__ val; int /*<<< orphan*/ * identifier; } ;

/* Variables and functions */
 TYPE_2__* stack ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *get_string(const char *identifier) {
    for (int c = 0; c < 10; c++) {
        if (stack[c].identifier == NULL)
            break;
        if (strcmp(identifier, stack[c].identifier) == 0)
            return stack[c].val.str;
    }
    return NULL;
}