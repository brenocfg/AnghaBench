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

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct object**,scalar_t__,int /*<<< orphan*/ ) ; 
 struct object** seen_objects ; 
 int /*<<< orphan*/  seen_objects_alloc ; 
 scalar_t__ seen_objects_nr ; 

__attribute__((used)) static inline void mark_as_seen(struct object *object)
{
	ALLOC_GROW(seen_objects, seen_objects_nr + 1, seen_objects_alloc);
	seen_objects[seen_objects_nr++] = object;
}