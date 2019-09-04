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

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 int replace_object_oid (char const*,struct object_id*,char const*,struct object_id*,int) ; 

__attribute__((used)) static int replace_object(const char *object_ref, const char *replace_ref, int force)
{
	struct object_id object, repl;

	if (get_oid(object_ref, &object))
		return error(_("failed to resolve '%s' as a valid ref"),
			     object_ref);
	if (get_oid(replace_ref, &repl))
		return error(_("failed to resolve '%s' as a valid ref"),
			     replace_ref);

	return replace_object_oid(object_ref, &object, replace_ref, &repl, force);
}