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

/* Variables and functions */
 int /*<<< orphan*/  MFI_DCMD_CFG_FOREIGN_DISPLAY ; 
 int display_format (int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
show_foreign(int ac, char **av)
{
	return(display_format(ac, av, 0/*normal display*/, MFI_DCMD_CFG_FOREIGN_DISPLAY));
}