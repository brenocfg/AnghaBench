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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
struct run_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int run_write (struct run_softc*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
run_set_region_4(struct run_softc *sc, uint16_t reg, uint32_t val, int len)
{
	int i, error = 0;

	KASSERT((len & 3) == 0, ("run_set_region_4: Invalid data length.\n"));
	for (i = 0; i < len && error == 0; i += 4)
		error = run_write(sc, reg + i, val);
	return (error);
}