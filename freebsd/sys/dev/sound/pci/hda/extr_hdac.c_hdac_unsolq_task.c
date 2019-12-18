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
struct hdac_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hdac_lock (struct hdac_softc*) ; 
 int /*<<< orphan*/  hdac_unlock (struct hdac_softc*) ; 
 int /*<<< orphan*/  hdac_unsolq_flush (struct hdac_softc*) ; 

__attribute__((used)) static void
hdac_unsolq_task(void *context, int pending)
{
	struct hdac_softc *sc;

	sc = (struct hdac_softc *)context;

	hdac_lock(sc);
	hdac_unsolq_flush(sc);
	hdac_unlock(sc);
}