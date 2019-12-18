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
struct ioc_vol {int* vol; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDIOCSETVOL ; 
 int /*<<< orphan*/  fd ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ioc_vol*) ; 

__attribute__((used)) static int
setvol(int left, int right)
{
	struct ioc_vol  v;

	left  = left  < 0 ? 0 : left  > 255 ? 255 : left;
	right = right < 0 ? 0 : right > 255 ? 255 : right;

	v.vol[0] = left;
	v.vol[1] = right;
	v.vol[2] = 0;
	v.vol[3] = 0;

	return ioctl (fd, CDIOCSETVOL, &v);
}