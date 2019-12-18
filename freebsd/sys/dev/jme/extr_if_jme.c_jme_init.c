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
struct jme_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_LOCK (struct jme_softc*) ; 
 int /*<<< orphan*/  JME_UNLOCK (struct jme_softc*) ; 
 int /*<<< orphan*/  jme_init_locked (struct jme_softc*) ; 

__attribute__((used)) static void
jme_init(void *xsc)
{
	struct jme_softc *sc;

	sc = (struct jme_softc *)xsc;
	JME_LOCK(sc);
	jme_init_locked(sc);
	JME_UNLOCK(sc);
}