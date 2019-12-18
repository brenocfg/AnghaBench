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
struct object {int /*<<< orphan*/  oid; } ;
struct bitmap_show_data {int /*<<< orphan*/  base; int /*<<< orphan*/  bitmap_git; } ;

/* Variables and functions */
 int bitmap_position (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,int) ; 
 int ext_index_add_object (int /*<<< orphan*/ ,struct object*,char const*) ; 

__attribute__((used)) static void show_object(struct object *object, const char *name, void *data_)
{
	struct bitmap_show_data *data = data_;
	int bitmap_pos;

	bitmap_pos = bitmap_position(data->bitmap_git, &object->oid);

	if (bitmap_pos < 0)
		bitmap_pos = ext_index_add_object(data->bitmap_git, object,
						  name);

	bitmap_set(data->base, bitmap_pos);
}