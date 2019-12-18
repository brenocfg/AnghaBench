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
 int /*<<< orphan*/  LINK_SLIST (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_next ; 
 int /*<<< orphan*/  mon_free ; 

__attribute__((used)) static inline void
mon_free_entry(
	mon_entry *m
	)
{
	ZERO(*m);
	LINK_SLIST(mon_free, m, hash_next);
}