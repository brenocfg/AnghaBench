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
struct mon_table {int type; int /*<<< orphan*/  flags; int /*<<< orphan*/ * f; } ;
typedef  enum monitor_reqtype { ____Placeholder_monitor_reqtype } monitor_reqtype ;

/* Variables and functions */
 int /*<<< orphan*/  MON_PERMIT ; 

__attribute__((used)) static void
monitor_permit(struct mon_table *ent, enum monitor_reqtype type, int permit)
{
	while (ent->f != NULL) {
		if (ent->type == type) {
			ent->flags &= ~MON_PERMIT;
			ent->flags |= permit ? MON_PERMIT : 0;
			return;
		}
		ent++;
	}
}