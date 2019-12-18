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
struct object {int dummy; } ;
struct name_decoration {int type; int /*<<< orphan*/  next; } ;
typedef  enum decoration_type { ____Placeholder_decoration_type } decoration_type ;

/* Variables and functions */
 int /*<<< orphan*/  FLEX_ALLOC_STR (struct name_decoration*,char const*,char const*) ; 
 int /*<<< orphan*/  add_decoration (int /*<<< orphan*/ *,struct object*,struct name_decoration*) ; 
 int /*<<< orphan*/  name_decoration ; 

void add_name_decoration(enum decoration_type type, const char *name, struct object *obj)
{
	struct name_decoration *res;
	FLEX_ALLOC_STR(res, name, name);
	res->type = type;
	res->next = add_decoration(&name_decoration, obj, res);
}