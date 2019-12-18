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
struct TYPE_2__ {int* class_agents; } ;

/* Variables and functions */
 int MAX_CLASS ; 
 TYPE_1__* ibmp ; 

int mad_class_agent(int mgmt)
{
	if (mgmt < 1 || mgmt >= MAX_CLASS)
		return -1;
	return ibmp->class_agents[mgmt];
}