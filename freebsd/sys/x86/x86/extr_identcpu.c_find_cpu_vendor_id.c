#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_3__ {int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_vendor ; 
 TYPE_1__* cpu_vendors ; 
 int nitems (TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
find_cpu_vendor_id(void)
{
	int	i;

	for (i = 0; i < nitems(cpu_vendors); i++)
		if (strcmp(cpu_vendor, cpu_vendors[i].vendor) == 0)
			return (cpu_vendors[i].vendor_id);
	return (0);
}