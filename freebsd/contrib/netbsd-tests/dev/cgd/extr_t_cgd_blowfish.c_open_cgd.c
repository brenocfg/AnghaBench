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
 int /*<<< orphan*/  O_RDWR ; 
 scalar_t__ getrawpartition () ; 
 int rump_sys_open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,scalar_t__) ; 

__attribute__((used)) static int
open_cgd(int devno)
{
	char devpath[32];

	sprintf(devpath, "/dev/rcgd%d%c", devno, getrawpartition() + 'a');

	return rump_sys_open(devpath, O_RDWR, 0);
}