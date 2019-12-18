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
struct ena_admin_aq_common_desc {int flags; } ;

/* Variables and functions */
 int ENA_ADMIN_AQ_COMMON_DESC_CTRL_DATA_INDIRECT_MASK ; 
 int ENA_ADMIN_AQ_COMMON_DESC_CTRL_DATA_INDIRECT_SHIFT ; 

__attribute__((used)) static inline uint8_t get_ena_admin_aq_common_desc_ctrl_data_indirect(const struct ena_admin_aq_common_desc *p)
{
	return (p->flags & ENA_ADMIN_AQ_COMMON_DESC_CTRL_DATA_INDIRECT_MASK) >> ENA_ADMIN_AQ_COMMON_DESC_CTRL_DATA_INDIRECT_SHIFT;
}