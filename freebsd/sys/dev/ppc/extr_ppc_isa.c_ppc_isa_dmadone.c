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
struct ppc_data {int /*<<< orphan*/  ppc_dmachan; int /*<<< orphan*/  ppc_dmacnt; int /*<<< orphan*/  ppc_dmaddr; int /*<<< orphan*/  ppc_dmaflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  isa_dmadone (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ppc_isa_dmadone(struct ppc_data *ppc)
{
	isa_dmadone(ppc->ppc_dmaflags, ppc->ppc_dmaddr, ppc->ppc_dmacnt,
	    ppc->ppc_dmachan);
}