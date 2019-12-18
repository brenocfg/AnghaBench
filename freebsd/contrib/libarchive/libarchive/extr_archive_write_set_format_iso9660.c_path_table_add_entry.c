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
struct path_table {int /*<<< orphan*/  cnt; struct isoent** last; } ;
struct isoent {struct isoent* ptnext; } ;

/* Variables and functions */

__attribute__((used)) static inline void
path_table_add_entry(struct path_table *pathtbl, struct isoent *ent)
{
	ent->ptnext = NULL;
	*pathtbl->last = ent;
	pathtbl->last = &(ent->ptnext);
	pathtbl->cnt ++;
}