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
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SC_FUNC (struct bxe_softc*) ; 
 int /*<<< orphan*/  storm_memset_eq_prod (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
bxe_update_eq_prod(struct bxe_softc *sc,
                   uint16_t         prod)
{
    storm_memset_eq_prod(sc, prod, SC_FUNC(sc));
    wmb(); /* keep prod updates ordered */
}