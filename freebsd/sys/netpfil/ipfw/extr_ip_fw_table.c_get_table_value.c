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
typedef  size_t uint32_t ;
struct table_value {int dummy; } ;
struct table_config {int dummy; } ;
struct ip_fw_chain {scalar_t__ valuestate; } ;

/* Variables and functions */

__attribute__((used)) static struct table_value *
get_table_value(struct ip_fw_chain *ch, struct table_config *tc, uint32_t kidx)
{
	struct table_value *pval;

	pval = (struct table_value *)ch->valuestate;

	return (&pval[kidx]);
}