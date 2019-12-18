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
struct xor_cb {int dummy; } ;
struct ppc440spe_adma_desc_slot {int dst_cnt; scalar_t__ src_cnt; int /*<<< orphan*/ * hw_next; int /*<<< orphan*/  hw_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ppc440spe_desc_init_null_xor(struct ppc440spe_adma_desc_slot *desc)
{
	memset(desc->hw_desc, 0, sizeof(struct xor_cb));
	desc->hw_next = NULL;
	desc->src_cnt = 0;
	desc->dst_cnt = 1;
}