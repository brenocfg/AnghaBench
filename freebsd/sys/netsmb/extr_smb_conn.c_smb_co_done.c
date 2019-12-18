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
struct smb_connobj {scalar_t__ co_lockcnt; scalar_t__ co_flags; int /*<<< orphan*/ * co_locker; int /*<<< orphan*/  co_lock; int /*<<< orphan*/  co_interlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
smb_co_done(struct smb_connobj *cp)
{

	sx_destroy(&cp->co_interlock);
	cv_destroy(&cp->co_lock);
	cp->co_locker = NULL;
	cp->co_flags = 0;
	cp->co_lockcnt = 0;
}