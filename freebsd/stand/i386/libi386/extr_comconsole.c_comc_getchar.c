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
 scalar_t__ com_data ; 
 scalar_t__ comc_ischar () ; 
 scalar_t__ comc_port ; 
 int inb (scalar_t__) ; 

__attribute__((used)) static int
comc_getchar(void)
{
	return (comc_ischar() ? inb(comc_port + com_data) : -1);
}