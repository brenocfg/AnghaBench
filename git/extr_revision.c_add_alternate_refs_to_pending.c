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
struct rev_info {int dummy; } ;
struct add_alternate_refs_data {unsigned int flags; struct rev_info* revs; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_one_alternate_ref ; 
 int /*<<< orphan*/  for_each_alternate_ref (int /*<<< orphan*/ ,struct add_alternate_refs_data*) ; 

__attribute__((used)) static void add_alternate_refs_to_pending(struct rev_info *revs,
					  unsigned int flags)
{
	struct add_alternate_refs_data data;
	data.revs = revs;
	data.flags = flags;
	for_each_alternate_ref(add_one_alternate_ref, &data);
}