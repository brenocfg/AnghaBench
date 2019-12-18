#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  eio; } ;
struct siba_erom {TYPE_1__ io; } ;
typedef  int /*<<< orphan*/  bhnd_erom_t ;

/* Variables and functions */
 int /*<<< orphan*/  bhnd_erom_io_fini (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
siba_erom_fini(bhnd_erom_t *erom)
{
	struct siba_erom *sc = (struct siba_erom *)erom;

	bhnd_erom_io_fini(sc->io.eio);
}