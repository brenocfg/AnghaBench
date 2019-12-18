#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_modules; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_ICL ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* sc ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_slock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_sunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
icl_unload(void)
{

	sx_slock(&sc->sc_lock);
	KASSERT(TAILQ_EMPTY(&sc->sc_modules), ("still have modules"));
	sx_sunlock(&sc->sc_lock);

	sx_destroy(&sc->sc_lock);
	free(sc, M_ICL);

	return (0);
}