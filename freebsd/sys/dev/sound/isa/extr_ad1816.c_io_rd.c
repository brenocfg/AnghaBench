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
struct ad1816_info {int /*<<< orphan*/  io_base; } ;

/* Variables and functions */
 int port_rd (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
io_rd(struct ad1816_info *ad1816, int reg)
{
	return port_rd(ad1816->io_base, reg);
}