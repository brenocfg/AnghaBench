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
struct ng_parse_type {struct ng_parse_struct_field* info; } ;
struct ng_parse_struct_field {int /*<<< orphan*/  type; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int ALIGNMENT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_struct_getAlign(const struct ng_parse_type *type)
{
	const struct ng_parse_struct_field *field;
	int align = 0;

	for (field = type->info; field->name != NULL; field++) {
		int falign = ALIGNMENT(field->type);

		if (falign > align)
			align = falign;
	}
	return align;
}