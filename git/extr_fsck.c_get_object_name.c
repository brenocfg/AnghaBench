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
struct fsck_options {int /*<<< orphan*/  object_names; } ;

/* Variables and functions */
 char* lookup_decoration (int /*<<< orphan*/ ,struct object*) ; 

__attribute__((used)) static char *get_object_name(struct fsck_options *options, struct object *obj)
{
	if (!options->object_names)
		return NULL;
	return lookup_decoration(options->object_names, obj);
}