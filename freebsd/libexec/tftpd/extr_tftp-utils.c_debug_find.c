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
struct TYPE_2__ {int value; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 TYPE_1__* debugs ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ *,char*) ; 

int
debug_find(char *s)
{
	int i = 0;

	while (debugs[i].name != NULL) {
		if (strcasecmp(debugs[i].name, s) == 0)
			break;
		i++;
	}
	return (debugs[i].value);
}