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
struct ena_admin_feature_rss_ind_table {int flags; } ;

/* Variables and functions */
 int ENA_ADMIN_FEATURE_RSS_IND_TABLE_ONE_ENTRY_UPDATE_MASK ; 

__attribute__((used)) static inline void set_ena_admin_feature_rss_ind_table_one_entry_update(struct ena_admin_feature_rss_ind_table *p, uint8_t val)
{
	p->flags |= val & ENA_ADMIN_FEATURE_RSS_IND_TABLE_ONE_ENTRY_UPDATE_MASK;
}