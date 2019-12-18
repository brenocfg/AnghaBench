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
struct mon_table {int flags; int /*<<< orphan*/ * f; } ;

/* Variables and functions */
 int MON_AUTH ; 
 int MON_PERMIT ; 
 struct mon_table* mon_dispatch ; 

__attribute__((used)) static void
monitor_permit_authentications(int permit)
{
	struct mon_table *ent = mon_dispatch;

	while (ent->f != NULL) {
		if (ent->flags & MON_AUTH) {
			ent->flags &= ~MON_PERMIT;
			ent->flags |= permit ? MON_PERMIT : 0;
		}
		ent++;
	}
}