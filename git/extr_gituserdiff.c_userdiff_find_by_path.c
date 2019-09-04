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
struct userdiff_driver {int dummy; } ;
struct index_state {int dummy; } ;
struct attr_check {TYPE_1__* items; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 scalar_t__ ATTR_FALSE (int /*<<< orphan*/ ) ; 
 scalar_t__ ATTR_TRUE (int /*<<< orphan*/ ) ; 
 scalar_t__ ATTR_UNSET (int /*<<< orphan*/ ) ; 
 struct attr_check* attr_check_initl (char*,int /*<<< orphan*/ *) ; 
 struct userdiff_driver driver_false ; 
 struct userdiff_driver driver_true ; 
 int /*<<< orphan*/  git_check_attr (struct index_state*,char const*,struct attr_check*) ; 
 struct userdiff_driver* userdiff_find_by_name (int /*<<< orphan*/ ) ; 

struct userdiff_driver *userdiff_find_by_path(struct index_state *istate,
					      const char *path)
{
	static struct attr_check *check;

	if (!check)
		check = attr_check_initl("diff", NULL);
	if (!path)
		return NULL;
	git_check_attr(istate, path, check);

	if (ATTR_TRUE(check->items[0].value))
		return &driver_true;
	if (ATTR_FALSE(check->items[0].value))
		return &driver_false;
	if (ATTR_UNSET(check->items[0].value))
		return NULL;
	return userdiff_find_by_name(check->items[0].value);
}