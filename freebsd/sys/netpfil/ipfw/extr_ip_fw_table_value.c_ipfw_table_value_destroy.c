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
struct ip_fw_chain {int /*<<< orphan*/  valuestate; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAIN_TO_VI (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_DEL_SOPT_HANDLER (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_IPFW ; 
 int /*<<< orphan*/  destroy_value ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipfw_objhash_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipfw_objhash_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ip_fw_chain*) ; 
 int /*<<< orphan*/  scodes ; 

void
ipfw_table_value_destroy(struct ip_fw_chain *ch, int last)
{

	IPFW_DEL_SOPT_HANDLER(last, scodes);

	free(ch->valuestate, M_IPFW);
	ipfw_objhash_foreach(CHAIN_TO_VI(ch), destroy_value, ch);
	ipfw_objhash_destroy(CHAIN_TO_VI(ch));
}