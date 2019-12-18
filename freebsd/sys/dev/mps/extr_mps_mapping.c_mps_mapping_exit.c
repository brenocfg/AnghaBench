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
struct mps_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _mapping_flush_dpm_pages (struct mps_softc*) ; 
 int /*<<< orphan*/  mps_mapping_free_memory (struct mps_softc*) ; 

void
mps_mapping_exit(struct mps_softc *sc)
{
	_mapping_flush_dpm_pages(sc);
	mps_mapping_free_memory(sc);
}