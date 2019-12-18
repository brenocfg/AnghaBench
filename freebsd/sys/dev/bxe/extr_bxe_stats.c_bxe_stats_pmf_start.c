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
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bxe_stats_comp (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_stats_pmf_update (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_stats_start (struct bxe_softc*) ; 

__attribute__((used)) static void
bxe_stats_pmf_start(struct bxe_softc *sc)
{
    bxe_stats_comp(sc);
    bxe_stats_pmf_update(sc);
    bxe_stats_start(sc);
}