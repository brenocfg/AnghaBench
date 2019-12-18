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
struct TYPE_2__ {int /*<<< orphan*/  val; scalar_t__ name; } ;
typedef  int /*<<< orphan*/  LogLevel ;

/* Variables and functions */
 int /*<<< orphan*/  SYSLOG_LEVEL_NOT_SET ; 
 TYPE_1__* log_levels ; 
 scalar_t__ strcasecmp (scalar_t__,char*) ; 

LogLevel
log_level_number(char *name)
{
	int i;

	if (name != NULL)
		for (i = 0; log_levels[i].name; i++)
			if (strcasecmp(log_levels[i].name, name) == 0)
				return log_levels[i].val;
	return SYSLOG_LEVEL_NOT_SET;
}