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
typedef  int /*<<< orphan*/  u_int32_t ;
struct sc_info {int /*<<< orphan*/  sh; int /*<<< orphan*/  st; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALS_GCR_DATA ; 
 int /*<<< orphan*/  ALS_GCR_INDEX ; 
 int /*<<< orphan*/  bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u_int32_t
als_gcr_rd(struct sc_info *sc, int index)
{
	bus_space_write_1(sc->st, sc->sh, ALS_GCR_INDEX, index);
	return bus_space_read_4(sc->st, sc->sh, ALS_GCR_DATA);
}