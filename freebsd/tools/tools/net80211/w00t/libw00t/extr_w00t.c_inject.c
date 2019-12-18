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
 int inject_params (int,void*,int,int /*<<< orphan*/ *) ; 

int inject(int fd, void *buf, int len)
{
	return inject_params(fd, buf, len, NULL);
}