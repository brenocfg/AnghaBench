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
struct sc_info {int /*<<< orphan*/  nambarh; int /*<<< orphan*/  nambart; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_space_write_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ich_waitcd (struct sc_info*) ; 

__attribute__((used)) static int
ich_wrcd(kobj_t obj, void *devinfo, int regno, uint32_t data)
{
	struct sc_info *sc = (struct sc_info *)devinfo;

	regno &= 0xff;
	ich_waitcd(sc);
	bus_space_write_2(sc->nambart, sc->nambarh, regno, data);

	return (0);
}