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
typedef  int /*<<< orphan*/  mon_entry ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_INSIST (int) ; 
 int /*<<< orphan*/  UNLINK_DLIST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mru ; 
 int /*<<< orphan*/  remove_from_hash (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
mon_reclaim_entry(
	mon_entry *m
	)
{
	DEBUG_INSIST(NULL != m);

	UNLINK_DLIST(m, mru);
	remove_from_hash(m);
	ZERO(*m);
}