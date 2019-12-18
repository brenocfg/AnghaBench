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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int bus_space_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bus_space_read_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (struct resource*) ; 
 int /*<<< orphan*/  rman_get_bustag (struct resource*) ; 

__attribute__((used)) static int
port_rd(struct resource *port, int regno, int size)
{
	bus_space_tag_t st = rman_get_bustag(port);
	bus_space_handle_t sh = rman_get_bushandle(port);

	switch (size) {
	case 1:
		return bus_space_read_1(st, sh, regno);
	case 2:
		return bus_space_read_2(st, sh, regno);
	case 4:
		return bus_space_read_4(st, sh, regno);
	default:
		return 0xffffffff;
	}
}