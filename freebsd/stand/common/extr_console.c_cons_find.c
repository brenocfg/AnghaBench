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
struct TYPE_2__ {int /*<<< orphan*/  c_name; } ;

/* Variables and functions */
 TYPE_1__** consoles ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
cons_find(const char *name)
{
    int		cons;

    for (cons = 0; consoles[cons] != NULL; cons++)
	if (!strcmp(consoles[cons]->c_name, name))
	    return (cons);
    return (-1);
}