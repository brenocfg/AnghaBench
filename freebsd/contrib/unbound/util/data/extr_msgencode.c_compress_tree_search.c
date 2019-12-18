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
struct compress_tree_node {struct compress_tree_node* right; struct compress_tree_node* left; int /*<<< orphan*/  labs; int /*<<< orphan*/  dname; } ;

/* Variables and functions */
 int dname_lab_cmp (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
compress_tree_search(struct compress_tree_node** tree, uint8_t* dname,
	int labs, struct compress_tree_node** match, int* matchlabels,
	struct compress_tree_node*** insertpt)
{
	int c, n, closen=0;
	struct compress_tree_node* p = *tree;
	struct compress_tree_node* close = 0;
	struct compress_tree_node** prev = tree;
	while(p) {
		if((c = dname_lab_cmp(dname, labs, p->dname, p->labs, &n)) 
			== 0) {
			*matchlabels = n;
			*match = p;
			return 1;
		}
		if(c<0) {
			prev = &p->left;
			p = p->left;
		} else	{
			closen = n;
			close = p; /* p->dname is smaller than dname */
			prev = &p->right;
			p = p->right;
		}
	}
	*insertpt = prev;
	*matchlabels = closen;
	*match = close;
	return 0;
}