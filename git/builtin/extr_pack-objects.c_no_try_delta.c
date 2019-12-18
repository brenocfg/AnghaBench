#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct attr_check {TYPE_1__* items; } ;
struct TYPE_4__ {int /*<<< orphan*/  index; } ;
struct TYPE_3__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 scalar_t__ ATTR_FALSE (int /*<<< orphan*/ ) ; 
 struct attr_check* attr_check_initl (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_check_attr (int /*<<< orphan*/ ,char const*,struct attr_check*) ; 
 TYPE_2__* the_repository ; 

__attribute__((used)) static int no_try_delta(const char *path)
{
	static struct attr_check *check;

	if (!check)
		check = attr_check_initl("delta", NULL);
	git_check_attr(the_repository->index, path, check);
	if (ATTR_FALSE(check->items[0].value))
		return 1;
	return 0;
}