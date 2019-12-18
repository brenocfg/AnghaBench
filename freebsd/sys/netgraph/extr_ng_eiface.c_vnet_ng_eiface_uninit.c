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
 int /*<<< orphan*/  V_ng_eiface_unit ; 
 int /*<<< orphan*/  delete_unrhdr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vnet_ng_eiface_uninit(const void *unused)
{

	delete_unrhdr(V_ng_eiface_unit);
}