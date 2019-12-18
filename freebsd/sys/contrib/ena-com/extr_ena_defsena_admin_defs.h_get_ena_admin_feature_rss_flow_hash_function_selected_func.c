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
struct ena_admin_feature_rss_flow_hash_function {int selected_func; } ;

/* Variables and functions */
 int ENA_ADMIN_FEATURE_RSS_FLOW_HASH_FUNCTION_SELECTED_FUNC_MASK ; 

__attribute__((used)) static inline uint32_t get_ena_admin_feature_rss_flow_hash_function_selected_func(const struct ena_admin_feature_rss_flow_hash_function *p)
{
	return p->selected_func & ENA_ADMIN_FEATURE_RSS_FLOW_HASH_FUNCTION_SELECTED_FUNC_MASK;
}