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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct run_softc {int dummy; } ;

/* Variables and functions */
 int run_write_2 (struct run_softc*,scalar_t__,int) ; 

__attribute__((used)) static int
run_write(struct run_softc *sc, uint16_t reg, uint32_t val)
{
	int error;

	if ((error = run_write_2(sc, reg, val & 0xffff)) == 0)
		error = run_write_2(sc, reg + 2, val >> 16);
	return (error);
}