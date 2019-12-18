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
typedef  size_t u_int ;
struct TYPE_2__ {char const* name; scalar_t__ val; } ;
typedef  scalar_t__ LogLevel ;

/* Variables and functions */
 TYPE_1__* log_levels ; 

const char *
log_level_name(LogLevel level)
{
	u_int i;

	for (i = 0; log_levels[i].name != NULL; i++)
		if (log_levels[i].val == level)
			return log_levels[i].name;
	return NULL;
}