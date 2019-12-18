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
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_object_entry (struct object_id const*,int,char*,int /*<<< orphan*/ ) ; 
 int oid_object_info (int /*<<< orphan*/ ,struct object_id const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int add_loose_object(const struct object_id *oid, const char *path,
			    void *data)
{
	enum object_type type = oid_object_info(the_repository, oid, NULL);

	if (type < 0) {
		warning(_("loose object at %s could not be examined"), path);
		return 0;
	}

	add_object_entry(oid, type, "", 0);
	return 0;
}