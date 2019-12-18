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
struct rwlock {int dummy; } ;
struct knlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  knlist_init (struct knlist*,struct rwlock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knlist_rw_assert_locked ; 
 int /*<<< orphan*/  knlist_rw_assert_unlocked ; 
 int /*<<< orphan*/  knlist_rw_rlock ; 
 int /*<<< orphan*/  knlist_rw_runlock ; 

void
knlist_init_rw_reader(struct knlist *knl, struct rwlock *lock)
{

	knlist_init(knl, lock, knlist_rw_rlock, knlist_rw_runlock,
	    knlist_rw_assert_locked, knlist_rw_assert_unlocked);
}