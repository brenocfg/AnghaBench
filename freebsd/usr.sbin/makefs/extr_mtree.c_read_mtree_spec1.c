#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_10__ {char const* name; struct TYPE_10__* first; struct TYPE_10__* child; struct TYPE_10__* next; int /*<<< orphan*/  type; struct TYPE_10__* parent; } ;
typedef  TYPE_1__ fsnode ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ENOMEM ; 
 int IS_DOT (char const*) ; 
 scalar_t__ IS_DOTDOT (char const*) ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* create_node (char const*,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  destroy_node (TYPE_1__*) ; 
 int /*<<< orphan*/  dupsok ; 
 TYPE_1__* mtree_current ; 
 int /*<<< orphan*/  mtree_error (char*,char const*) ; 
 TYPE_1__ mtree_global ; 
 TYPE_1__* mtree_root ; 
 int /*<<< orphan*/  mtree_warning (char*,...) ; 
 int read_mtree_keywords (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static int
read_mtree_spec1(FILE *fp, bool def, const char *name)
{
	fsnode *last, *node, *parent;
	u_int type;
	int error;

	assert(name[0] != '\0');

	/*
	 * Treat '..' specially, because it only changes our current
	 * directory. We don't create a node for it. We simply ignore
	 * any keywords that may appear on the line as well.
	 * Going up a directory is a little non-obvious. A directory
	 * node has a corresponding '.' child. The parent of '.' is
	 * not the '.' node of the parent directory, but the directory
	 * node within the parent to which the child relates. However,
	 * going up a directory means we need to find the '.' node to
	 * which the directoy node is linked.  This we can do via the
	 * first * pointer, because '.' is always the first entry in a
	 * directory.
	 */
	if (IS_DOTDOT(name)) {
		/* This deals with NULL pointers as well. */
		if (mtree_current == mtree_root) {
			mtree_warning("ignoring .. in root directory");
			return (0);
		}

		node = mtree_current;

		assert(node != NULL);
		assert(IS_DOT(node->name));
		assert(node->first == node);

		/* Get the corresponding directory node in the parent. */
		node = mtree_current->parent;

		assert(node != NULL);
		assert(!IS_DOT(node->name));

		node = node->first;

		assert(node != NULL);
		assert(IS_DOT(node->name));
		assert(node->first == node);

		mtree_current = node;
		return (0);
	}

	/*
	 * If we don't have a current directory and the first specification
	 * (either implicit or defined) is not '.', then we need to create
	 * a '.' node first (using a recursive call).
	 */
	if (!IS_DOT(name) && mtree_current == NULL) {
		error = read_mtree_spec1(fp, false, ".");
		if (error)
			return (error);
	}

	/*
	 * Lookup the name in the current directory (if we have a current
	 * directory) to make sure we do not create multiple nodes for the
	 * same component. For non-definitions, if we find a node with the
	 * same name, simply change the current directory. For definitions
	 * more happens.
	 */
	last = NULL;
	node = mtree_current;
	while (node != NULL) {
		assert(node->first == mtree_current);

		if (strcmp(name, node->name) == 0) {
			if (def == true) {
				if (!dupsok)
					mtree_error(
					    "duplicate definition of %s",
					    name);
				else
					mtree_warning(
					    "duplicate definition of %s",
					    name);
				return (0);
			}

			if (node->type != S_IFDIR) {
				mtree_error("%s is not a directory", name);
				return (0);
			}

			assert(!IS_DOT(name));

			node = node->child;

			assert(node != NULL);
			assert(IS_DOT(node->name));

			mtree_current = node;
			return (0);
		}

		last = node;
		node = last->next;
	}

	parent = (mtree_current != NULL) ? mtree_current->parent : NULL;
	type = (def == false || IS_DOT(name)) ? S_IFDIR : 0;
	node = create_node(name, type, parent, &mtree_global);
	if (node == NULL)
		return (ENOMEM);

	if (def == true) {
		error = read_mtree_keywords(fp, node);
		if (error) {
			destroy_node(node);
			return (error);
		}
	}

	node->first = (mtree_current != NULL) ? mtree_current : node;

	if (last != NULL)
		last->next = node;

	if (node->type != S_IFDIR)
		return (0);

	if (!IS_DOT(node->name)) {
		parent = node;
		node = create_node(".", S_IFDIR, parent, parent);
		if (node == NULL) {
			last->next = NULL;
			destroy_node(parent);
			return (ENOMEM);
		}
		parent->child = node;
		node->first = node;
	}

	assert(node != NULL);
	assert(IS_DOT(node->name));
	assert(node->first == node);

	mtree_current = node;
	if (mtree_root == NULL)
		mtree_root = node;

	return (0);
}