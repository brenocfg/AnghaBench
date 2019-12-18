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
typedef  int /*<<< orphan*/  u_int8_t ;
struct sc_info {int /*<<< orphan*/  enh_sh; int /*<<< orphan*/  enh_st; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_space_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int8_t
sv_direct_get(struct sc_info *sc, u_int8_t reg)
{
	return bus_space_read_1(sc->enh_st, sc->enh_sh, reg);
}