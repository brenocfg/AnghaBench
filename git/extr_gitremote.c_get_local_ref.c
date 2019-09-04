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
struct ref {int dummy; } ;

/* Variables and functions */
 struct ref* alloc_ref (char const*) ; 
 struct ref* alloc_ref_with_prefix (char*,int,char const*) ; 
 scalar_t__ starts_with (char const*,char*) ; 

__attribute__((used)) static struct ref *get_local_ref(const char *name)
{
	if (!name || name[0] == '\0')
		return NULL;

	if (starts_with(name, "refs/"))
		return alloc_ref(name);

	if (starts_with(name, "heads/") ||
	    starts_with(name, "tags/") ||
	    starts_with(name, "remotes/"))
		return alloc_ref_with_prefix("refs/", 5, name);

	return alloc_ref_with_prefix("refs/heads/", 11, name);
}