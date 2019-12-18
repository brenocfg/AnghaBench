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
struct submodule_update_strategy {int type; int /*<<< orphan*/ * command; } ;
typedef  enum submodule_update_type { ____Placeholder_submodule_update_type } submodule_update_type ;

/* Variables and functions */
 int SM_UPDATE_COMMAND ; 
 int SM_UPDATE_UNSPECIFIED ; 
 int /*<<< orphan*/  free (void*) ; 
 int parse_submodule_update_type (char const*) ; 
 int /*<<< orphan*/ * xstrdup (char const*) ; 

int parse_submodule_update_strategy(const char *value,
		struct submodule_update_strategy *dst)
{
	enum submodule_update_type type;

	free((void*)dst->command);
	dst->command = NULL;

	type = parse_submodule_update_type(value);
	if (type == SM_UPDATE_UNSPECIFIED)
		return -1;

	dst->type = type;
	if (type == SM_UPDATE_COMMAND)
		dst->command = xstrdup(value + 1);

	return 0;
}