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
typedef  int /*<<< orphan*/  uint16_t ;
struct ckb_softc {int cols; int rows; int /*<<< orphan*/ * keymap; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static uint16_t
keymap_read(struct ckb_softc *sc, int col, int row)
{

	KASSERT(sc->keymap != NULL, ("keymap_read: no keymap"));
	if (col >= 0 && col < sc->cols &&
	    row >= 0 && row < sc->rows) {
		return sc->keymap[row * sc->cols + col];
	}

	return (0);
}