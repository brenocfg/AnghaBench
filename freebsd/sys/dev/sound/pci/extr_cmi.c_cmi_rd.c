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
typedef  int u_int32_t ;
struct sc_info {int /*<<< orphan*/  sh; int /*<<< orphan*/  st; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int bus_space_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bus_space_read_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static u_int32_t
cmi_rd(struct sc_info *sc, int regno, int size)
{
	switch (size) {
	case 1:
		return bus_space_read_1(sc->st, sc->sh, regno);
	case 2:
		return bus_space_read_2(sc->st, sc->sh, regno);
	case 4:
		return bus_space_read_4(sc->st, sc->sh, regno);
	default:
		DEB(printf("cmi_rd: failed 0x%04x %d\n", regno, size));
		return 0xFFFFFFFF;
	}
}