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
struct branch {char const** merge_name; scalar_t__ merge_nr; int /*<<< orphan*/  merge_alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (char const**,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_merge(struct branch *branch, const char *name)
{
	ALLOC_GROW(branch->merge_name, branch->merge_nr + 1,
		   branch->merge_alloc);
	branch->merge_name[branch->merge_nr++] = name;
}