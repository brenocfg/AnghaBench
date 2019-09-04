#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int numweights; TYPE_1__* weights; } ;
typedef  TYPE_2__ weightconfig_t ;
struct TYPE_5__ {TYPE_2__* name; int /*<<< orphan*/  firstseperator; } ;

/* Variables and functions */
 int /*<<< orphan*/  FreeFuzzySeperators_r (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeMemory (TYPE_2__*) ; 

void FreeWeightConfig2(weightconfig_t *config)
{
	int i;

	for (i = 0; i < config->numweights; i++)
	{
		FreeFuzzySeperators_r(config->weights[i].firstseperator);
		if (config->weights[i].name) FreeMemory(config->weights[i].name);
	} //end for
	FreeMemory(config);
}