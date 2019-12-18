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
 int /*<<< orphan*/  __dmadat ; 
 int bootdev ; 
 int /*<<< orphan*/ * dmadat ; 
 scalar_t__ fsread (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ofw_open (char const*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
domount(const char *device)
{

	if ((bootdev = ofw_open(device)) == -1) {
		printf("domount: can't open device\n");
		return (-1);
	}
#ifndef ZFSBOOT
	dmadat = &__dmadat;
	if (fsread(0, NULL, 0)) {
		printf("domount: can't read superblock\n");
		return (-1);
	}
#endif
	return (0);
}