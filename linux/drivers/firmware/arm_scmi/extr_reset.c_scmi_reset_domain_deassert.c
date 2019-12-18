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
struct scmi_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCH_COLD_RESET ; 
 int scmi_domain_reset (struct scmi_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
scmi_reset_domain_deassert(const struct scmi_handle *handle, u32 domain)
{
	return scmi_domain_reset(handle, domain, 0, ARCH_COLD_RESET);
}