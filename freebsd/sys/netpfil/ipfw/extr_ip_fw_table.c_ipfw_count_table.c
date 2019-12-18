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
typedef  int /*<<< orphan*/  uint32_t ;
struct tid_info {int dummy; } ;
struct table_config {int dummy; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAIN_TO_NI (struct ip_fw_chain*) ; 
 int ESRCH ; 
 struct table_config* find_table (int /*<<< orphan*/ ,struct tid_info*) ; 
 int /*<<< orphan*/  table_get_count (struct ip_fw_chain*,struct table_config*) ; 

int
ipfw_count_table(struct ip_fw_chain *ch, struct tid_info *ti, uint32_t *cnt)
{
	struct table_config *tc;

	if ((tc = find_table(CHAIN_TO_NI(ch), ti)) == NULL)
		return (ESRCH);
	*cnt = table_get_count(ch, tc);
	return (0);
}