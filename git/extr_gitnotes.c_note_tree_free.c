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
struct int_node {void** a; } ;

/* Variables and functions */
 struct int_node* CLR_PTR_TYPE (void*) ; 
 int GET_PTR_TYPE (void*) ; 
#define  PTR_TYPE_INTERNAL 130 
#define  PTR_TYPE_NOTE 129 
#define  PTR_TYPE_SUBTREE 128 
 int /*<<< orphan*/  free (struct int_node*) ; 

__attribute__((used)) static void note_tree_free(struct int_node *tree)
{
	unsigned int i;
	for (i = 0; i < 16; i++) {
		void *p = tree->a[i];
		switch (GET_PTR_TYPE(p)) {
		case PTR_TYPE_INTERNAL:
			note_tree_free(CLR_PTR_TYPE(p));
			/* fall through */
		case PTR_TYPE_NOTE:
		case PTR_TYPE_SUBTREE:
			free(CLR_PTR_TYPE(p));
		}
	}
}