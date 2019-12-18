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
typedef  enum alias { ____Placeholder_alias } alias ;
struct TYPE_2__ {int alias; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int ALIAS_NONE ; 
 TYPE_1__* scheme_alias ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static enum alias
scheme_parse_alias(const char *name)
{
	u_int idx;

	idx = 0;
	while (scheme_alias[idx].name != NULL) {
		if (strcasecmp(scheme_alias[idx].name, name) == 0)
			return (scheme_alias[idx].alias);
		idx++;
	}
	return (ALIAS_NONE);
}