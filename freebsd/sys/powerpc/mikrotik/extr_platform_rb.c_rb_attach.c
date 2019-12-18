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
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int mpc85xx_attach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rb_attach(platform_t plat)
{
	int error;

	error = mpc85xx_attach(plat);
	if (error)
		return (error);

	return (0);
}