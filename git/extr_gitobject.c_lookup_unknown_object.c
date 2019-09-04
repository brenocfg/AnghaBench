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
 int /*<<< orphan*/  alloc_object_node (int /*<<< orphan*/ ) ; 
 struct object* create_object (int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ ) ; 
 struct object* lookup_object (int /*<<< orphan*/ ,unsigned char const*) ; 
 int /*<<< orphan*/  the_repository ; 

struct object *lookup_unknown_object(const unsigned char *sha1)
{
	struct object *obj = lookup_object(the_repository, sha1);
	if (!obj)
		obj = create_object(the_repository, sha1,
				    alloc_object_node(the_repository));
	return obj;
}