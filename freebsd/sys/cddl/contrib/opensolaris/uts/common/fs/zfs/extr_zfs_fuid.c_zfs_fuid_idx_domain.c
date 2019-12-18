#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {TYPE_1__* f_ksid; int /*<<< orphan*/  f_idx; } ;
typedef  TYPE_2__ fuid_domain_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;
typedef  int /*<<< orphan*/  avl_index_t ;
struct TYPE_5__ {char* kd_name; } ;

/* Variables and functions */
 TYPE_2__* avl_find (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 char* nulldomain ; 

char *
zfs_fuid_idx_domain(avl_tree_t *idx_tree, uint32_t idx)
{
	fuid_domain_t searchnode, *findnode;
	avl_index_t loc;

	searchnode.f_idx = idx;

	findnode = avl_find(idx_tree, &searchnode, &loc);

	return (findnode ? findnode->f_ksid->kd_name : nulldomain);
}