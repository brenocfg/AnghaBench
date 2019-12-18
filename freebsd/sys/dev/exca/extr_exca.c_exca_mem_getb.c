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
typedef  int /*<<< orphan*/  uint8_t ;
struct exca_softc {scalar_t__ offset; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_space_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static uint8_t
exca_mem_getb(struct exca_softc *sc, int reg)
{
	return (bus_space_read_1(sc->bst, sc->bsh, sc->offset + reg));
}