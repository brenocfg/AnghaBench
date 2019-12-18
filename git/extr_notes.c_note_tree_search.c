#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct notes_tree {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hash; } ;
struct leaf_node {TYPE_1__ key_oid; } ;
struct int_node {void** a; } ;

/* Variables and functions */
 struct int_node* CLR_PTR_TYPE (void*) ; 
 unsigned char GET_NIBBLE (unsigned char,unsigned char const*) ; 
 int GET_PTR_TYPE (void*) ; 
#define  PTR_TYPE_INTERNAL 129 
#define  PTR_TYPE_SUBTREE 128 
 int /*<<< orphan*/  SUBTREE_SHA1_PREFIXCMP (unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct leaf_node*) ; 
 int /*<<< orphan*/  load_subtree (struct notes_tree*,struct leaf_node*,struct int_node*,unsigned char) ; 

__attribute__((used)) static void **note_tree_search(struct notes_tree *t, struct int_node **tree,
		unsigned char *n, const unsigned char *key_sha1)
{
	struct leaf_node *l;
	unsigned char i;
	void *p = (*tree)->a[0];

	if (GET_PTR_TYPE(p) == PTR_TYPE_SUBTREE) {
		l = (struct leaf_node *) CLR_PTR_TYPE(p);
		if (!SUBTREE_SHA1_PREFIXCMP(key_sha1, l->key_oid.hash)) {
			/* unpack tree and resume search */
			(*tree)->a[0] = NULL;
			load_subtree(t, l, *tree, *n);
			free(l);
			return note_tree_search(t, tree, n, key_sha1);
		}
	}

	i = GET_NIBBLE(*n, key_sha1);
	p = (*tree)->a[i];
	switch (GET_PTR_TYPE(p)) {
	case PTR_TYPE_INTERNAL:
		*tree = CLR_PTR_TYPE(p);
		(*n)++;
		return note_tree_search(t, tree, n, key_sha1);
	case PTR_TYPE_SUBTREE:
		l = (struct leaf_node *) CLR_PTR_TYPE(p);
		if (!SUBTREE_SHA1_PREFIXCMP(key_sha1, l->key_oid.hash)) {
			/* unpack tree and resume search */
			(*tree)->a[i] = NULL;
			load_subtree(t, l, *tree, *n);
			free(l);
			return note_tree_search(t, tree, n, key_sha1);
		}
		/* fall through */
	default:
		return &((*tree)->a[i]);
	}
}