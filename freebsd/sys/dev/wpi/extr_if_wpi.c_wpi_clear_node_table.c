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
struct wpi_softc {scalar_t__ nodesmsk; } ;

/* Variables and functions */

__attribute__((used)) static __inline void
wpi_clear_node_table(struct wpi_softc *sc)
{
	sc->nodesmsk = 0;
}