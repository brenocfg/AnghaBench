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
struct safe_softc {int dummy; } ;

/* Variables and functions */
 int READ_REG (struct safe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAFE_RNG_CTRL ; 
 int SAFE_RNG_CTRL_SHORTEN ; 
 int /*<<< orphan*/  WRITE_REG (struct safe_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline void
safe_rng_disable_short_cycle(struct safe_softc *sc)
{
	WRITE_REG(sc, SAFE_RNG_CTRL,
		READ_REG(sc, SAFE_RNG_CTRL) &~ SAFE_RNG_CTRL_SHORTEN);
}