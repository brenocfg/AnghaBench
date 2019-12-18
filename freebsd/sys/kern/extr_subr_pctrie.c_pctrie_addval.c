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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct pctrie_node {void** pn_child; } ;

/* Variables and functions */
 uintptr_t PCTRIE_ISLEAF ; 
 int pctrie_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
pctrie_addval(struct pctrie_node *node, uint64_t index, uint16_t clev,
    uint64_t *val)
{
	int slot;

	slot = pctrie_slot(index, clev);
	node->pn_child[slot] = (void *)((uintptr_t)val | PCTRIE_ISLEAF);
}