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
typedef  int bus_space_handle_t ;
typedef  int bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  readb (int) ; 

__attribute__((used)) static uint8_t
pcimem_bs_r_1_s(void *t, bus_space_handle_t h, bus_size_t o)
{

	return readb(h + (o &~ 3) + (3 - (o & 3)));
}