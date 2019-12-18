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
struct uv_hub_nmi_s {scalar_t__ pch_owner; scalar_t__ hub_present; } ;

/* Variables and functions */
 int uv_nmi_test_hubless (struct uv_hub_nmi_s*) ; 
 int uv_nmi_test_mmr (struct uv_hub_nmi_s*) ; 

__attribute__((used)) static int uv_test_nmi(struct uv_hub_nmi_s *hub_nmi)
{
	if (hub_nmi->hub_present)
		return uv_nmi_test_mmr(hub_nmi);

	if (hub_nmi->pch_owner)		/* Only PCH owner can check status */
		return uv_nmi_test_hubless(hub_nmi);

	return -1;
}