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
typedef  void* uint64_t ;
struct sfs_node {void* sn_id; void* sn_parent_id; int /*<<< orphan*/  sn_name; } ;
typedef  struct sfs_node sfs_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_SFSNODES ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct sfs_node* malloc (size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static sfs_node_t *
sfs_alloc_node(size_t size, const char *name, uint64_t parent_id, uint64_t id)
{
	struct sfs_node *node;

	KASSERT(strlen(name) < sizeof(node->sn_name),
	    ("sfs node name is too long"));
	KASSERT(size >= sizeof(*node), ("sfs node size is too small"));
	node = malloc(size, M_SFSNODES, M_WAITOK | M_ZERO);
	strlcpy(node->sn_name, name, sizeof(node->sn_name));
	node->sn_parent_id = parent_id;
	node->sn_id = id;

	return (node);
}