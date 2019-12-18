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
 int /*<<< orphan*/  SIOCGETFF ; 
 int /*<<< orphan*/  fd ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ipferror (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ipfname ; 
 int opendevice (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static	int	get_flags()
{
	int i = 0;

	if ((opendevice(ipfname, 1) != -2) &&
	    (ioctl(fd, SIOCGETFF, &i) == -1)) {
		ipferror(fd, "SIOCGETFF");
		return 0;
	}
	return i;
}