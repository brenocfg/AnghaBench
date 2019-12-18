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
struct pfs_node {int dummy; } ;
struct pfs_info {int dummy; } ;
typedef  int /*<<< orphan*/  pfs_type_t ;

/* Variables and functions */
 struct pfs_node* pfs_alloc_node_flags (struct pfs_info*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pfs_node *
pfs_alloc_node(struct pfs_info *pi, const char *name, pfs_type_t type)
{
	return (pfs_alloc_node_flags(pi, name, type, 0));
}