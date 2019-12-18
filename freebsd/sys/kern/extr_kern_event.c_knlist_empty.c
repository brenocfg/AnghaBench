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
struct knlist {int /*<<< orphan*/  kl_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  KNL_ASSERT_LOCKED (struct knlist*) ; 
 int SLIST_EMPTY (int /*<<< orphan*/ *) ; 

int
knlist_empty(struct knlist *knl)
{

	KNL_ASSERT_LOCKED(knl);
	return (SLIST_EMPTY(&knl->kl_list));
}