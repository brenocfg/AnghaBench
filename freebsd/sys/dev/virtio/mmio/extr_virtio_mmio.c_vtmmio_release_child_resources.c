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
struct vtmmio_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vtmmio_free_interrupts (struct vtmmio_softc*) ; 
 int /*<<< orphan*/  vtmmio_free_virtqueues (struct vtmmio_softc*) ; 

__attribute__((used)) static void
vtmmio_release_child_resources(struct vtmmio_softc *sc)
{

	vtmmio_free_interrupts(sc);
	vtmmio_free_virtqueues(sc);
}