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
struct part {int /*<<< orphan*/ * label; int /*<<< orphan*/  type; int /*<<< orphan*/  alias; } ;
struct mkimg_alias {int alias; int /*<<< orphan*/  type; } ;
typedef  enum alias { ____Placeholder_alias } alias ;
struct TYPE_2__ {scalar_t__ labellen; struct mkimg_alias* aliases; } ;

/* Variables and functions */
 int ALIAS_NONE ; 
 int EINVAL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* scheme ; 
 int scheme_parse_alias (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 

int
scheme_check_part(struct part *p)
{
	struct mkimg_alias *iter;
	enum alias alias;

	assert(scheme != NULL);

	/* Check the partition type alias */
	alias = scheme_parse_alias(p->alias);
	if (alias == ALIAS_NONE)
		return (EINVAL);

	iter = scheme->aliases;
	while (iter->alias != ALIAS_NONE) {
		if (alias == iter->alias)
			break;
		iter++;
	}
	if (iter->alias == ALIAS_NONE)
		return (EINVAL);
	p->type = iter->type;

	/* Validate the optional label. */
	if (p->label != NULL) {
		if (strlen(p->label) > scheme->labellen)
			return (EINVAL);
	}

	return (0);
}