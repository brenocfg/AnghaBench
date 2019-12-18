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
struct object_entry {int type_valid; unsigned int type_; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int OBJ_ANY ; 
 int OBJ_NONE ; 

__attribute__((used)) static inline void oe_set_type(struct object_entry *e,
			       enum object_type type)
{
	if (type >= OBJ_ANY)
		BUG("OBJ_ANY cannot be set in pack-objects code");

	e->type_valid = type >= OBJ_NONE;
	e->type_ = (unsigned)type;
}