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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int SC_AUTO ; 
 TYPE_1__* convtbl ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

int
get_scale(const char *name)
{
	int i;

	for (i = 0; i <= SC_AUTO; i++)
		if (strcmp(convtbl[i].name, name) == 0)
			return (i);
	return (-1);
}