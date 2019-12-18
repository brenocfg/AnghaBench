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
typedef  scalar_t__ uint8_t ;
struct regional {int dummy; } ;
struct compress_tree_node {int labs; struct compress_tree_node* parent; struct compress_tree_node* right; } ;

/* Variables and functions */
 size_t PTR_MAX_OFFSET ; 
 struct compress_tree_node* compress_tree_newnode (scalar_t__*,int,size_t,struct regional*) ; 
 int /*<<< orphan*/  log_assert (int) ; 

__attribute__((used)) static int
compress_tree_store(uint8_t* dname, int labs, size_t offset, 
	struct regional* region, struct compress_tree_node* closest, 
	struct compress_tree_node** insertpt)
{
	uint8_t lablen;
	struct compress_tree_node* newnode;
	struct compress_tree_node* prevnode = NULL;
	int uplabs = labs-1; /* does not store root in tree */
	if(closest) uplabs = labs - closest->labs;
	log_assert(uplabs >= 0);
	/* algorithms builds up a vine of dname-labels to hang into tree */
	while(uplabs--) {
		if(offset > PTR_MAX_OFFSET) {
			/* insertion failed, drop vine */
			return 1; /* compression pointer no longer useful */
		}
		if(!(newnode = compress_tree_newnode(dname, labs, offset, 
			region))) {
			/* insertion failed, drop vine */
			return 0;
		}

		if(prevnode) {
			/* chain nodes together, last one has one label more,
			 * so is larger than newnode, thus goes right. */
			newnode->right = prevnode;
			prevnode->parent = newnode;
		}

		/* next label */
		lablen = *dname++;
		dname += lablen;
		offset += lablen+1;
		prevnode = newnode;
		labs--;
	}
	/* if we have a vine, hang the vine into the tree */
	if(prevnode) {
		*insertpt = prevnode;
		prevnode->parent = closest;
	}
	return 1;
}