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
struct resource {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_write_1 (struct resource*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pmio_write(struct resource *res, uint8_t reg, uint8_t val)
{
	bus_write_1(res, 0, reg);	/* Index */
	bus_write_1(res, 1, val);	/* Data */
}