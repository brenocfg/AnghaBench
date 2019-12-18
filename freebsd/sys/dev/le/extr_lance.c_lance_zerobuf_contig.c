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
struct lance_softc {scalar_t__ sc_mem; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (scalar_t__ volatile,int /*<<< orphan*/ ,int) ; 

void
lance_zerobuf_contig(struct lance_softc *sc, int boff, int len)
{
	volatile caddr_t buf = sc->sc_mem;

	/*
	 * Just let memset() do the work
	 */
	memset(buf + boff, 0, len);
}