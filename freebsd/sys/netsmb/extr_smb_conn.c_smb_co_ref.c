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
struct smb_connobj {int /*<<< orphan*/  co_interlock; int /*<<< orphan*/  co_usecount; } ;

/* Variables and functions */
 int /*<<< orphan*/  sx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 

void
smb_co_ref(struct smb_connobj *cp)
{

	sx_xlock(&cp->co_interlock);
	cp->co_usecount++;
	sx_unlock(&cp->co_interlock);
}