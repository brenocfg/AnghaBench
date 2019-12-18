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
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  SNOOP1 ; 
 int /*<<< orphan*/  SNOOP2 ; 
 int SNOOP_RANGE_2GB ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
set_snooping(bus_space_tag_t iot, bus_space_handle_t ioh)
{

	bus_space_write_4(iot, ioh, SNOOP1, SNOOP_RANGE_2GB);
	bus_space_write_4(iot, ioh, SNOOP2, 0x80000000 | SNOOP_RANGE_2GB);
}