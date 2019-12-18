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
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ DEV_STA_OPEN ; 
 int UB_MAX_DEV ; 
 TYPE_1__* devices ; 

__attribute__((used)) static int
dev_valid(int handle)
{

	if (handle < 0 || handle >= UB_MAX_DEV)
		return (0);

	if (devices[handle].state != DEV_STA_OPEN)
		return (0);

	return (1);
}