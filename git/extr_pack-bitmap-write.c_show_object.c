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
struct bitmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_set (struct bitmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_object_pos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_as_seen (struct object*) ; 

__attribute__((used)) static void show_object(struct object *object, const char *name, void *data)
{
	struct bitmap *base = data;
	bitmap_set(base, find_object_pos(&object->oid));
	mark_as_seen(object);
}