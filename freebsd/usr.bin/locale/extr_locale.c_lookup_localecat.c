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
struct TYPE_2__ {int id; char const* name; } ;

/* Variables and functions */
 size_t NLCINFO ; 
 TYPE_1__* lcinfo ; 

const char *
lookup_localecat(int cat)
{
	size_t	i;

	for (i = 0; i < NLCINFO; i++)
		if (lcinfo[i].id == cat) {
			return (lcinfo[i].name);
		}
	return ("UNKNOWN");
}