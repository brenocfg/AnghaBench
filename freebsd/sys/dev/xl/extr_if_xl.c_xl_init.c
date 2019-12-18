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
struct xl_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XL_LOCK (struct xl_softc*) ; 
 int /*<<< orphan*/  XL_UNLOCK (struct xl_softc*) ; 
 int /*<<< orphan*/  xl_init_locked (struct xl_softc*) ; 

__attribute__((used)) static void
xl_init(void *xsc)
{
	struct xl_softc		*sc = xsc;

	XL_LOCK(sc);
	xl_init_locked(sc);
	XL_UNLOCK(sc);
}