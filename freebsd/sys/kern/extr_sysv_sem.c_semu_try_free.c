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
struct sem_undo {scalar_t__ un_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct sem_undo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct sem_undo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  SEMUNDO_LOCKASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  semu_free_list ; 
 int /*<<< orphan*/  un_next ; 

__attribute__((used)) static int
semu_try_free(struct sem_undo *suptr)
{

	SEMUNDO_LOCKASSERT(MA_OWNED);

	if (suptr->un_cnt != 0)
		return (0);
	LIST_REMOVE(suptr, un_next);
	LIST_INSERT_HEAD(&semu_free_list, suptr, un_next);
	return (1);
}