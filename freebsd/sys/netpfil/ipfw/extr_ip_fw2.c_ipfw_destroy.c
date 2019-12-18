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
 int /*<<< orphan*/  ipfw_destroy_obj_rewriter () ; 
 int /*<<< orphan*/  ipfw_destroy_sopt_handler () ; 
 int /*<<< orphan*/  ipfw_iface_destroy () ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
ipfw_destroy(void)
{

	ipfw_iface_destroy();
	ipfw_destroy_sopt_handler();
	ipfw_destroy_obj_rewriter();
	printf("IP firewall unloaded\n");
}