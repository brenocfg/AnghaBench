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
typedef  enum trailer_where { ____Placeholder_trailer_where } trailer_where ;

/* Variables and functions */
 int WHERE_AFTER ; 
 int WHERE_BEFORE ; 
 int WHERE_DEFAULT ; 
 int WHERE_END ; 
 int WHERE_START ; 
 int /*<<< orphan*/  strcasecmp (char*,char const*) ; 

int trailer_set_where(enum trailer_where *item, const char *value)
{
	if (!value)
		*item = WHERE_DEFAULT;
	else if (!strcasecmp("after", value))
		*item = WHERE_AFTER;
	else if (!strcasecmp("before", value))
		*item = WHERE_BEFORE;
	else if (!strcasecmp("end", value))
		*item = WHERE_END;
	else if (!strcasecmp("start", value))
		*item = WHERE_START;
	else
		return -1;
	return 0;
}