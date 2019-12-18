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
struct ng_parse_type {struct ng_parse_fixedarray_info* info; } ;
struct ng_parse_fixedarray_info {int /*<<< orphan*/  elementType; } ;

/* Variables and functions */
 int ALIGNMENT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_fixedarray_getAlign(const struct ng_parse_type *type)
{
	const struct ng_parse_fixedarray_info *fi = type->info;

	return ALIGNMENT(fi->elementType);
}