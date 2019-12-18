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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  ior; } ;
struct nct_softc {TYPE_1__ cache; } ;

/* Variables and functions */
 int nct_get_pin_cache (struct nct_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
nct_pin_is_input(struct nct_softc *sc, uint32_t pin_num)
{
	return (nct_get_pin_cache(sc, pin_num, sc->cache.ior));
}