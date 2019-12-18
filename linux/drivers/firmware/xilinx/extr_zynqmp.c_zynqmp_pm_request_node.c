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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum zynqmp_pm_request_ack { ____Placeholder_zynqmp_pm_request_ack } zynqmp_pm_request_ack ;

/* Variables and functions */
 int /*<<< orphan*/  PM_REQUEST_NODE ; 
 int zynqmp_pm_invoke_fn (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zynqmp_pm_request_node(const u32 node, const u32 capabilities,
				  const u32 qos,
				  const enum zynqmp_pm_request_ack ack)
{
	return zynqmp_pm_invoke_fn(PM_REQUEST_NODE, node, capabilities,
				   qos, ack, NULL);
}