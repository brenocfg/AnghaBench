#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int GIT_HASH_NALGOS ; 
 int GIT_HASH_UNKNOWN ; 
 TYPE_1__* hash_algos ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

int hash_algo_by_name(const char *name)
{
	int i;
	if (!name)
		return GIT_HASH_UNKNOWN;
	for (i = 1; i < GIT_HASH_NALGOS; i++)
		if (!strcmp(name, hash_algos[i].name))
			return i;
	return GIT_HASH_UNKNOWN;
}