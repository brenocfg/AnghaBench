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
struct lanai_dev {int base; } ;
typedef  enum lanai_register { ____Placeholder_lanai_register } lanai_register ;
typedef  int bus_addr_t ;

/* Variables and functions */

__attribute__((used)) static inline bus_addr_t reg_addr(const struct lanai_dev *lanai,
	enum lanai_register reg)
{
	return lanai->base + reg;
}