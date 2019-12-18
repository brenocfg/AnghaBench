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
struct resource {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_write_1 (struct resource*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
nvt_conf_exit(struct resource* res, uint16_t port)
{
	bus_write_1(res, 0, 0xaa);
}