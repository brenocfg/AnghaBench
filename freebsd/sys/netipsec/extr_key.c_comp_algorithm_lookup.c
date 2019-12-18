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
struct comp_algo {int dummy; } ;
struct TYPE_3__ {int sadb_alg; struct comp_algo const* xform; } ;

/* Variables and functions */
 int nitems (TYPE_1__*) ; 
 TYPE_1__* supported_calgs ; 

const struct comp_algo *
comp_algorithm_lookup(int alg)
{
	int i;

	for (i = 0; i < nitems(supported_calgs); i++)
		if (alg == supported_calgs[i].sadb_alg)
			return (supported_calgs[i].xform);
	return (NULL);
}