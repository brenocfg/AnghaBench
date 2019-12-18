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
struct ptnet_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTNET_CORE_LOCK (struct ptnet_softc*) ; 
 int /*<<< orphan*/  PTNET_CORE_UNLOCK (struct ptnet_softc*) ; 
 int /*<<< orphan*/  ptnet_init_locked (struct ptnet_softc*) ; 

__attribute__((used)) static void
ptnet_init(void *opaque)
{
	struct ptnet_softc *sc = opaque;

	PTNET_CORE_LOCK(sc);
	ptnet_init_locked(sc);
	PTNET_CORE_UNLOCK(sc);
}