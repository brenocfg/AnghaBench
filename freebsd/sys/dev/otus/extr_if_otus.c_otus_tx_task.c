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
struct otus_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OTUS_LOCK (struct otus_softc*) ; 
 int /*<<< orphan*/  OTUS_UNLOCK (struct otus_softc*) ; 
 int /*<<< orphan*/  _otus_start (struct otus_softc*) ; 

__attribute__((used)) static void
otus_tx_task(void *arg, int pending)
{
	struct otus_softc *sc = arg;

	OTUS_LOCK(sc);
	_otus_start(sc);
	OTUS_UNLOCK(sc);
}