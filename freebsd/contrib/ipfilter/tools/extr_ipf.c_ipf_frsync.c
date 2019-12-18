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
 int /*<<< orphan*/  SIOCFRSYN ; 
 int /*<<< orphan*/  fd ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ipferror (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ipfname ; 
 int opendevice (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

void ipf_frsync()
{
	int frsyn = 0;

	if (opendevice(ipfname, 1) != -2 && ioctl(fd, SIOCFRSYN, &frsyn) == -1)
		ipferror(fd, "SIOCFRSYN");
	else
		printf("filter sync'd\n");
}