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
struct TYPE_5__ {int /*<<< orphan*/  read; } ;
struct TYPE_6__ {int /*<<< orphan*/ * tree; TYPE_1__ reader; } ;
typedef  TYPE_2__ tree_reader ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_reader ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* git__calloc (int,int) ; 
 int /*<<< orphan*/  tree_reader_read ; 

int git_reader_for_tree(git_reader **out, git_tree *tree)
{
	tree_reader *reader;

	assert(out && tree);

	reader = git__calloc(1, sizeof(tree_reader));
	GIT_ERROR_CHECK_ALLOC(reader);

	reader->reader.read = tree_reader_read;
	reader->tree = tree;

	*out = (git_reader *)reader;
	return 0;
}