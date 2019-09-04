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
typedef  int /*<<< orphan*/  tree_iterator ;
typedef  int /*<<< orphan*/  git_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  tree_iterator_clear (int /*<<< orphan*/ *) ; 
 int tree_iterator_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tree_iterator_reset(git_iterator *i)
{
	tree_iterator *iter = (tree_iterator *)i;

	tree_iterator_clear(iter);
	return tree_iterator_init(iter);
}