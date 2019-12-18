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
struct ena_admin_get_set_feature_common_desc {int flags; } ;

/* Variables and functions */
 int ENA_ADMIN_GET_SET_FEATURE_COMMON_DESC_SELECT_MASK ; 

__attribute__((used)) static inline void set_ena_admin_get_set_feature_common_desc_select(struct ena_admin_get_set_feature_common_desc *p, uint8_t val)
{
	p->flags |= val & ENA_ADMIN_GET_SET_FEATURE_COMMON_DESC_SELECT_MASK;
}