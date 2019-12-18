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
 scalar_t__ kh_end (int /*<<< orphan*/ *) ; 
 scalar_t__ kh_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  str ; 

int git_strmap_exists(git_strmap *map, const char *key)
{
	return kh_get(str, map, key) != kh_end(map);
}