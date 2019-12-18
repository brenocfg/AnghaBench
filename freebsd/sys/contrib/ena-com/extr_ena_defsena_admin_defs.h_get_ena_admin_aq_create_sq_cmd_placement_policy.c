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
typedef  int uint8_t ;
struct ena_admin_aq_create_sq_cmd {int sq_caps_2; } ;

/* Variables and functions */
 int ENA_ADMIN_AQ_CREATE_SQ_CMD_PLACEMENT_POLICY_MASK ; 

__attribute__((used)) static inline uint8_t get_ena_admin_aq_create_sq_cmd_placement_policy(const struct ena_admin_aq_create_sq_cmd *p)
{
	return p->sq_caps_2 & ENA_ADMIN_AQ_CREATE_SQ_CMD_PLACEMENT_POLICY_MASK;
}