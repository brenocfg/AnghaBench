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
 scalar_t__ is64bit ; 

__attribute__((used)) static int align(int n)
{
	if (is64bit)
		return (n + 0x1fff) & ~0x1fff;
	else
		return (n + 0xfff) & ~0xfff;
}