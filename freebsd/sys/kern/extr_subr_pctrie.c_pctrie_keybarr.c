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
typedef  scalar_t__ uint64_t ;
struct pctrie_node {scalar_t__ pn_clev; scalar_t__ pn_owner; } ;

/* Variables and functions */
 scalar_t__ PCTRIE_LIMIT ; 
 scalar_t__ pctrie_trimkey (scalar_t__,scalar_t__) ; 

__attribute__((used)) static __inline bool
pctrie_keybarr(struct pctrie_node *node, uint64_t idx)
{

	if (node->pn_clev < PCTRIE_LIMIT) {
		idx = pctrie_trimkey(idx, node->pn_clev + 1);
		return (idx != node->pn_owner);
	}
	return (false);
}