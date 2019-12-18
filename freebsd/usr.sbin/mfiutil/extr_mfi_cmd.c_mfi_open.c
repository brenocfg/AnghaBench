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
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

int
mfi_open(int unit, int acs)
{
	char path[MAXPATHLEN];

	snprintf(path, sizeof(path), "/dev/mfi%d", unit);
	return (open(path, acs));
}