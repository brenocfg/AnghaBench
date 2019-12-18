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
 char const** w_reg ; 
 char const** x_reg ; 

__attribute__((used)) static const char *
arm64_reg(int b64, int num)
{

	if (b64 != 0)
		return (x_reg[num]);

	return (w_reg[num]);
}