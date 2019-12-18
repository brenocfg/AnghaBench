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
struct cgem_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGEM_LOCK (struct cgem_softc*) ; 
 int /*<<< orphan*/  CGEM_UNLOCK (struct cgem_softc*) ; 
 int /*<<< orphan*/  cgem_init_locked (struct cgem_softc*) ; 

__attribute__((used)) static void
cgem_init(void *arg)
{
	struct cgem_softc *sc = (struct cgem_softc *)arg;

	CGEM_LOCK(sc);
	cgem_init_locked(sc);
	CGEM_UNLOCK(sc);
}