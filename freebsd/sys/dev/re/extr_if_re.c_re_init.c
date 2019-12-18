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
struct rl_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RL_LOCK (struct rl_softc*) ; 
 int /*<<< orphan*/  RL_UNLOCK (struct rl_softc*) ; 
 int /*<<< orphan*/  re_init_locked (struct rl_softc*) ; 

__attribute__((used)) static void
re_init(void *xsc)
{
	struct rl_softc		*sc = xsc;

	RL_LOCK(sc);
	re_init_locked(sc);
	RL_UNLOCK(sc);
}