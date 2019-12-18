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
typedef  int /*<<< orphan*/  uint8_t ;
struct nct_softc {int /*<<< orphan*/  iores; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nct_io_set_group (struct nct_softc*,int) ; 

__attribute__((used)) static uint8_t
nct_io_read(struct nct_softc *sc, int group, uint8_t reg)
{
	nct_io_set_group(sc, group);
	return (bus_read_1(sc->iores, reg));
}