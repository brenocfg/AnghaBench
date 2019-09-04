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
typedef  int /*<<< orphan*/  git_strmap ;

/* Variables and functions */
 size_t kh_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kh_exist (int /*<<< orphan*/ *,size_t) ; 
 size_t kh_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 void* kh_val (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  str ; 

void *git_strmap_get(git_strmap *map, const char *key)
{
	size_t idx = kh_get(str, map, key);
	if (idx == kh_end(map) || !kh_exist(map, idx))
		return NULL;
	return kh_val(map, idx);
}