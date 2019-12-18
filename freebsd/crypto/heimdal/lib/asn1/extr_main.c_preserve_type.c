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
struct TYPE_2__ {int num_strings; int /*<<< orphan*/ * strings; } ;

/* Variables and functions */
 TYPE_1__ preserve ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

int
preserve_type(const char *p)
{
    int i;
    for (i = 0; i < preserve.num_strings; i++)
	if (strcmp(preserve.strings[i], p) == 0)
	    return 1;
    return 0;
}