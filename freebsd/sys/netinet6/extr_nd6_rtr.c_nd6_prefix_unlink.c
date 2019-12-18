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
struct nd_prhead {int dummy; } ;
struct nd_prefix {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (struct nd_prhead*,struct nd_prefix*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct nd_prefix*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND6_WLOCK_ASSERT () ; 
 int /*<<< orphan*/  V_nd6_list_genid ; 
 int /*<<< orphan*/  ndpr_entry ; 

void
nd6_prefix_unlink(struct nd_prefix *pr, struct nd_prhead *list)
{

	ND6_WLOCK_ASSERT();

	LIST_REMOVE(pr, ndpr_entry);
	V_nd6_list_genid++;
	if (list != NULL)
		LIST_INSERT_HEAD(list, pr, ndpr_entry);
}