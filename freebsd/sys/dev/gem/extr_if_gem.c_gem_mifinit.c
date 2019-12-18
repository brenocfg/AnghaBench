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
struct gem_softc {int dummy; } ;

/* Variables and functions */
 int BUS_SPACE_BARRIER_READ ; 
 int BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  GEM_BANK1_BARRIER (struct gem_softc*,int /*<<< orphan*/ ,int,int) ; 
 int GEM_BANK1_READ_4 (struct gem_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_BANK1_WRITE_4 (struct gem_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GEM_MIF_CONFIG ; 
 int GEM_MIF_CONFIG_BB_ENA ; 

__attribute__((used)) static void
gem_mifinit(struct gem_softc *sc)
{

	/* Configure the MIF in frame mode. */
	GEM_BANK1_WRITE_4(sc, GEM_MIF_CONFIG,
	    GEM_BANK1_READ_4(sc, GEM_MIF_CONFIG) & ~GEM_MIF_CONFIG_BB_ENA);
	GEM_BANK1_BARRIER(sc, GEM_MIF_CONFIG, 4,
	    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
}