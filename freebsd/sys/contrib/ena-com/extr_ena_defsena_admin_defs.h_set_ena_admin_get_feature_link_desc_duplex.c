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
typedef  int uint32_t ;
struct ena_admin_get_feature_link_desc {int flags; } ;

/* Variables and functions */
 int ENA_ADMIN_GET_FEATURE_LINK_DESC_DUPLEX_MASK ; 
 int ENA_ADMIN_GET_FEATURE_LINK_DESC_DUPLEX_SHIFT ; 

__attribute__((used)) static inline void set_ena_admin_get_feature_link_desc_duplex(struct ena_admin_get_feature_link_desc *p, uint32_t val)
{
	p->flags |= (val << ENA_ADMIN_GET_FEATURE_LINK_DESC_DUPLEX_SHIFT) & ENA_ADMIN_GET_FEATURE_LINK_DESC_DUPLEX_MASK;
}