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
typedef  int /*<<< orphan*/  uint8_t ;
struct regional {int dummy; } ;
struct compress_tree_node {int labs; size_t offset; int /*<<< orphan*/ * dname; scalar_t__ parent; scalar_t__ right; scalar_t__ left; } ;

/* Variables and functions */
 scalar_t__ regional_alloc (struct regional*,int) ; 

__attribute__((used)) static struct compress_tree_node*
compress_tree_newnode(uint8_t* dname, int labs, size_t offset, 
	struct regional* region)
{
	struct compress_tree_node* n = (struct compress_tree_node*)
		regional_alloc(region, sizeof(struct compress_tree_node));
	if(!n) return 0;
	n->left = 0;
	n->right = 0;
	n->parent = 0;
	n->dname = dname;
	n->labs = labs;
	n->offset = offset;
	return n;
}