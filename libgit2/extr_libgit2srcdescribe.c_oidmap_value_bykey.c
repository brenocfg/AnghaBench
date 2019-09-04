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
typedef  int /*<<< orphan*/  git_oidmap ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 void* git_oidmap_get (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void *oidmap_value_bykey(git_oidmap *map, const git_oid *key)
{
	return git_oidmap_get(map, key);
}