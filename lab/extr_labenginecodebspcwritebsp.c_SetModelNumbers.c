#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ numbrushes; } ;

/* Variables and functions */
 int /*<<< orphan*/  SetKeyValue (TYPE_1__*,char*,char*) ; 
 TYPE_1__* entities ; 
 int num_entities ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void SetModelNumbers (void)
{
	int		i;
	int		models;
	char	value[10];

	models = 1;
	for (i=1 ; i<num_entities ; i++)
	{
		if (entities[i].numbrushes)
		{
			sprintf (value, "*%i", models);
			models++;
			SetKeyValue (&entities[i], "model", value);
		}
	}

}