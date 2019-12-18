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
struct mpr_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _mapping_flush_dpm_pages (struct mpr_softc*) ; 
 int /*<<< orphan*/  mpr_mapping_free_memory (struct mpr_softc*) ; 

void
mpr_mapping_exit(struct mpr_softc *sc)
{
	_mapping_flush_dpm_pages(sc);
	mpr_mapping_free_memory(sc);
}