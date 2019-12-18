#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_sessions; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_1__* sc ; 
 int /*<<< orphan*/  sx_slock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_sunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
iscsi_quiesce(void)
{
	sx_slock(&sc->sc_lock);
	if (!TAILQ_EMPTY(&sc->sc_sessions)) {
		sx_sunlock(&sc->sc_lock);
		return (EBUSY);
	}
	sx_sunlock(&sc->sc_lock);
	return (0);
}