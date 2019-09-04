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
typedef  int /*<<< orphan*/  config_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 int git_config_from_blob_oid (int /*<<< orphan*/ ,char const*,struct object_id*,void*) ; 

__attribute__((used)) static int git_config_from_blob_ref(config_fn_t fn,
				    const char *name,
				    void *data)
{
	struct object_id oid;

	if (get_oid(name, &oid) < 0)
		return error(_("unable to resolve config blob '%s'"), name);
	return git_config_from_blob_oid(fn, name, &oid, data);
}