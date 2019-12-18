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
 void* rtld_dlopen (int /*<<< orphan*/ *,int,int) ; 

void *
fdlopen(int fd, int mode)
{

	return (rtld_dlopen(NULL, fd, mode));
}