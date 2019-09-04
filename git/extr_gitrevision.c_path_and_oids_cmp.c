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
struct path_and_oids_entry {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int path_and_oids_cmp(const void *hashmap_cmp_fn_data,
			     const struct path_and_oids_entry *e1,
			     const struct path_and_oids_entry *e2,
			     const void *keydata)
{
	return strcmp(e1->path, e2->path);
}