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
 scalar_t__ delete_ref (int /*<<< orphan*/ *,char const*,struct object_id const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_ln (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int delete_replace_ref(const char *name, const char *ref,
			      const struct object_id *oid)
{
	if (delete_ref(NULL, ref, oid, 0))
		return 1;
	printf_ln(_("Deleted replace ref '%s'"), name);
	return 0;
}