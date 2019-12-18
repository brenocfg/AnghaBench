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
 int /*<<< orphan*/  nat64_netisr ; 

void
nat64_set_output_method(int direct)
{

	V_nat64out = direct != 0 ? &nat64_direct: &nat64_netisr;
}