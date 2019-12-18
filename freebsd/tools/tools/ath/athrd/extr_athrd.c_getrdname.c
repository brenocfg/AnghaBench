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
struct TYPE_3__ {scalar_t__ rd; char const* name; } ;
typedef  scalar_t__ HAL_REG_DOMAIN ;

/* Variables and functions */
 TYPE_1__* domains ; 
 int nitems (TYPE_1__*) ; 

__attribute__((used)) static const char *
getrdname(HAL_REG_DOMAIN rd)
{
	int i;

	for (i = 0; i < nitems(domains); i++)
		if (domains[i].rd == rd)
			return domains[i].name;
	return NULL;
}