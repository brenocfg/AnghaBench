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
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  OFIOCGETOPTNODE ; 
 int /*<<< orphan*/  OFW_IOCTL (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

phandle_t
ofw_optnode(int fd)
{
	phandle_t rv;

	OFW_IOCTL(fd, OFIOCGETOPTNODE, &rv);
	return (rv);
}