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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int bus_space_handle_t ;
typedef  int bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
reversed_bs_w_2(void *t, bus_space_handle_t h, bus_size_t o, uint16_t v)
{

	writew(h + (o &~ 3) + (2 - (o & 3)), v);
}