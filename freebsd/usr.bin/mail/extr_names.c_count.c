#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct name {int n_type; struct name* n_flink; } ;

/* Variables and functions */
 int GDEL ; 

int
count(struct name *np)
{
	int c;

	for (c = 0; np != NULL; np = np->n_flink)
		if ((np->n_type & GDEL) == 0)
			c++;
	return (c);
}