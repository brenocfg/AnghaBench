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
typedef  scalar_t__ u_int32_t ;
struct safe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ READ_REG (struct safe_softc*,int /*<<< orphan*/ ) ; 
 int SAFE_RNG_MAXWAIT ; 
 int /*<<< orphan*/  SAFE_RNG_OUT ; 
 int /*<<< orphan*/  SAFE_RNG_STAT ; 

__attribute__((used)) static __inline u_int32_t
safe_rng_read(struct safe_softc *sc)
{
	int i;

	i = 0;
	while (READ_REG(sc, SAFE_RNG_STAT) != 0 && ++i < SAFE_RNG_MAXWAIT)
		;
	return READ_REG(sc, SAFE_RNG_OUT);
}