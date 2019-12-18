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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int mmc_get_rca (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int) ; 

__attribute__((used)) static int
mmc_child_location_str(device_t dev, device_t child, char *buf,
    size_t buflen)
{

	snprintf(buf, buflen, "rca=0x%04x", mmc_get_rca(child));
	return (0);
}