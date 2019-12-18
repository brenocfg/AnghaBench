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
struct TYPE_2__ {int type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int MAX_BUSTYPE ; 
 int UNKNOWN_BUSTYPE ; 
 TYPE_1__* bus_type_table ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
lookup_bus_type(char *name)
{
	int     x;

	for (x = 0; x < MAX_BUSTYPE; ++x)
		if (strncmp(bus_type_table[x].name, name, 6) == 0)
			return (bus_type_table[x].type);

	return (UNKNOWN_BUSTYPE);
}