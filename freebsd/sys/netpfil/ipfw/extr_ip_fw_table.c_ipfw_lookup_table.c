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
typedef  int /*<<< orphan*/  uint16_t ;
struct table_info {int (* lookup ) (struct table_info*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 struct table_info* KIDX_TO_TI (struct ip_fw_chain*,int /*<<< orphan*/ ) ; 
 int stub1 (struct table_info*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
ipfw_lookup_table(struct ip_fw_chain *ch, uint16_t tbl, uint16_t plen,
    void *paddr, uint32_t *val)
{
	struct table_info *ti;

	ti = KIDX_TO_TI(ch, tbl);

	return (ti->lookup(ti, paddr, plen, val));
}