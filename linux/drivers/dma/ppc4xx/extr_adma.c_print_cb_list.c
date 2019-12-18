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
struct ppc440spe_adma_desc_slot {int /*<<< orphan*/  hw_desc; struct ppc440spe_adma_desc_slot* hw_next; } ;
struct ppc440spe_adma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_cb (struct ppc440spe_adma_chan*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_cb_list(struct ppc440spe_adma_chan *chan,
			  struct ppc440spe_adma_desc_slot *iter)
{
	for (; iter; iter = iter->hw_next)
		print_cb(chan, iter->hw_desc);
}