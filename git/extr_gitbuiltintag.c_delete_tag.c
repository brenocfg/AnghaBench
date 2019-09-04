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
 int /*<<< orphan*/  DEFAULT_ABBREV ; 
 char* _ (char*) ; 
 scalar_t__ delete_ref (int /*<<< orphan*/ *,char const*,struct object_id const*,int /*<<< orphan*/ ) ; 
 char* find_unique_abbrev (struct object_id const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 

__attribute__((used)) static int delete_tag(const char *name, const char *ref,
		      const struct object_id *oid, const void *cb_data)
{
	if (delete_ref(NULL, ref, oid, 0))
		return 1;
	printf(_("Deleted tag '%s' (was %s)\n"), name,
	       find_unique_abbrev(oid, DEFAULT_ABBREV));
	return 0;
}