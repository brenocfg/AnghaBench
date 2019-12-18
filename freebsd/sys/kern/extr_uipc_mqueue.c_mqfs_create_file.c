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
struct ucred {int dummy; } ;
struct mqfs_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ mqfs_add_node (struct mqfs_node*,struct mqfs_node*) ; 
 struct mqfs_node* mqfs_create_node (char const*,int,struct ucred*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mqfstype_file ; 
 int /*<<< orphan*/  mqnode_free (struct mqfs_node*) ; 

__attribute__((used)) static struct mqfs_node *
mqfs_create_file(struct mqfs_node *parent, const char *name, int namelen,
	struct ucred *cred, int mode)
{
	struct mqfs_node *node;

	node = mqfs_create_node(name, namelen, cred, mode, mqfstype_file);
	if (mqfs_add_node(parent, node) != 0) {
		mqnode_free(node);
		return (NULL);
	}
	return (node);
}