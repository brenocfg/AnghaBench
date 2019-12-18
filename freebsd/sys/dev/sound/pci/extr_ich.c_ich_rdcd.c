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
struct sc_info {int /*<<< orphan*/  nambarh; int /*<<< orphan*/  nambart; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int bus_space_read_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ich_waitcd (struct sc_info*) ; 

__attribute__((used)) static int
ich_rdcd(kobj_t obj, void *devinfo, int regno)
{
	struct sc_info *sc = (struct sc_info *)devinfo;

	regno &= 0xff;
	ich_waitcd(sc);

	return (bus_space_read_2(sc->nambart, sc->nambarh, regno));
}