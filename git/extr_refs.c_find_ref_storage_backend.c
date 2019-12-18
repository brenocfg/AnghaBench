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
struct ref_storage_be {int /*<<< orphan*/  name; struct ref_storage_be* next; } ;

/* Variables and functions */
 struct ref_storage_be* refs_backends ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct ref_storage_be *find_ref_storage_backend(const char *name)
{
	struct ref_storage_be *be;
	for (be = refs_backends; be; be = be->next)
		if (!strcmp(be->name, name))
			return be;
	return NULL;
}