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
struct ecore_mcp_link_capabilities {int /*<<< orphan*/  speed_capabilities; } ;
struct ecore_bulletin_content {int /*<<< orphan*/  capability_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_mcp_link_capabilities*,int /*<<< orphan*/ ,int) ; 

void __ecore_vf_get_link_caps(struct ecore_mcp_link_capabilities *p_link_caps,
			      struct ecore_bulletin_content *p_bulletin)
{
	OSAL_MEMSET(p_link_caps, 0, sizeof(*p_link_caps));
	p_link_caps->speed_capabilities = p_bulletin->capability_speed;
}