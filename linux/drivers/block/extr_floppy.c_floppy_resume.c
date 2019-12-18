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
struct device {int dummy; } ;
struct TYPE_2__ {int address; } ;

/* Variables and functions */
 TYPE_1__* FDCS ; 
 int /*<<< orphan*/  FD_RESET_ALWAYS ; 
 int N_FDC ; 
 int /*<<< orphan*/  user_reset_fdc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int floppy_resume(struct device *dev)
{
	int fdc;

	for (fdc = 0; fdc < N_FDC; fdc++)
		if (FDCS->address != -1)
			user_reset_fdc(-1, FD_RESET_ALWAYS, false);

	return 0;
}