#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 int DEV_TYP_STOR ; 
 int /*<<< orphan*/  dev_valid (int) ; 
 TYPE_1__* devices ; 

__attribute__((used)) static int
dev_stor_valid(int handle)
{

	if (!dev_valid(handle))
		return (0);

	if (!(devices[handle].type & DEV_TYP_STOR))
		return (0);

	return (1);
}