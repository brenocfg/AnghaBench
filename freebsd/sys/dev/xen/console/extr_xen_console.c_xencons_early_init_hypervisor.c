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
struct xencons_priv {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
xencons_early_init_hypervisor(struct xencons_priv *cons)
{
	/*
	 * Nothing to setup for the low-level console when using
	 * the hypervisor console.
	 */
}