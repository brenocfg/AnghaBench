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
struct sysc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sysc_clk_quirk_i2c (struct sysc*,int) ; 

__attribute__((used)) static void sysc_clk_disable_quirk_i2c(struct sysc *ddata)
{
	sysc_clk_quirk_i2c(ddata, false);
}