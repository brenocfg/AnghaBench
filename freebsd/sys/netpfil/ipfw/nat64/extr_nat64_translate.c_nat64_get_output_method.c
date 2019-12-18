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
 int /*<<< orphan*/ * V_nat64out ; 
 int /*<<< orphan*/  nat64_direct ; 

int
nat64_get_output_method(void)
{

	return (V_nat64out == &nat64_direct ? 1: 0);
}