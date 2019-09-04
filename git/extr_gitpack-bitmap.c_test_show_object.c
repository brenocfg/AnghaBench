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
struct bitmap_test_data {int /*<<< orphan*/  seen; int /*<<< orphan*/  prg; int /*<<< orphan*/  base; int /*<<< orphan*/  bitmap_git; } ;

/* Variables and functions */
 int bitmap_position (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_progress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_show_object(struct object *object, const char *name,
			     void *data)
{
	struct bitmap_test_data *tdata = data;
	int bitmap_pos;

	bitmap_pos = bitmap_position(tdata->bitmap_git, &object->oid);
	if (bitmap_pos < 0)
		die("Object not in bitmap: %s\n", oid_to_hex(&object->oid));

	bitmap_set(tdata->base, bitmap_pos);
	display_progress(tdata->prg, ++tdata->seen);
}