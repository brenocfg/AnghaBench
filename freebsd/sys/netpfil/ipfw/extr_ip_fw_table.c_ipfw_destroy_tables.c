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
struct ip_fw_chain {int /*<<< orphan*/  tablestate; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAIN_TO_NI (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  CHAIN_TO_TCFG (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_DEL_OBJ_REWRITER (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPFW_DEL_SOPT_HANDLER (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  M_IPFW ; 
 int /*<<< orphan*/  destroy_table_locked ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipfw_objhash_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipfw_objhash_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ip_fw_chain*) ; 
 int /*<<< orphan*/  ipfw_table_algo_destroy (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  ipfw_table_value_destroy (struct ip_fw_chain*,int) ; 
 int /*<<< orphan*/  opcodes ; 
 int /*<<< orphan*/  scodes ; 

void
ipfw_destroy_tables(struct ip_fw_chain *ch, int last)
{

	IPFW_DEL_SOPT_HANDLER(last, scodes);
	IPFW_DEL_OBJ_REWRITER(last, opcodes);

	/* Remove all tables from working set */
	IPFW_UH_WLOCK(ch);
	IPFW_WLOCK(ch);
	ipfw_objhash_foreach(CHAIN_TO_NI(ch), destroy_table_locked, ch);
	IPFW_WUNLOCK(ch);
	IPFW_UH_WUNLOCK(ch);

	/* Free pointers itself */
	free(ch->tablestate, M_IPFW);

	ipfw_table_value_destroy(ch, last);
	ipfw_table_algo_destroy(ch);

	ipfw_objhash_destroy(CHAIN_TO_NI(ch));
	free(CHAIN_TO_TCFG(ch), M_IPFW);
}