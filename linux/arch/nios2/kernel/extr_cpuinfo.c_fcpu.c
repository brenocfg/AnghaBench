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
typedef  int /*<<< orphan*/  u32 ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u32 fcpu(struct device_node *cpu, const char *n)
{
	u32 val = 0;

	of_property_read_u32(cpu, n, &val);

	return val;
}