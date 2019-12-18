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
struct TYPE_2__ {char const* name; int value; } ;

/* Variables and functions */
 TYPE_1__* packettypes ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

const char *
packettype(int type)
{
	static char failed[100];
	int i = 0;

	while (packettypes[i].name != NULL) {
		if (packettypes[i].value == type)
			break;
		i++;
	}
	if (packettypes[i].name != NULL)
		return packettypes[i].name;
	sprintf(failed, "unknown (type: %d)", type);
	return (failed);
}