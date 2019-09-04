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
struct object_id {int dummy; } ;
struct object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 char const* oid_to_hex (struct object_id const*) ; 
 struct object* parse_object (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  the_repository ; 

struct object *parse_object_or_die(const struct object_id *oid,
				   const char *name)
{
	struct object *o = parse_object(the_repository, oid);
	if (o)
		return o;

	die(_("unable to parse object: %s"), name ? name : oid_to_hex(oid));
}