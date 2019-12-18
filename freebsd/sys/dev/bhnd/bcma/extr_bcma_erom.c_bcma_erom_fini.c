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
struct bcma_erom {int /*<<< orphan*/  eio; } ;
typedef  int /*<<< orphan*/  bhnd_erom_t ;

/* Variables and functions */
 int /*<<< orphan*/  bhnd_erom_io_fini (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bcma_erom_fini(bhnd_erom_t *erom)
{
	struct bcma_erom *sc = (struct bcma_erom *)erom;

	bhnd_erom_io_fini(sc->eio);
}