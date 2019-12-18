#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int entry_count; int children_count; struct TYPE_7__** children; int /*<<< orphan*/  oid; } ;
typedef  TYPE_1__ git_tree_cache ;
typedef  int /*<<< orphan*/  git_pool ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__**) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_MULTIPLY (size_t*,int,int) ; 
 int /*<<< orphan*/  GIT_ERROR_INDEX ; 
 int GIT_OID_RAWSZ ; 
 scalar_t__ git__strntol32 (int*,char const*,int,char const**,int) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_oid_fromraw (int /*<<< orphan*/ *,unsigned char const*) ; 
 TYPE_1__** git_pool_malloc (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ git_tree_cache_new (TYPE_1__**,char const*,int /*<<< orphan*/ *) ; 
 char* memchr (char const*,char,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__**,int,size_t) ; 

__attribute__((used)) static int read_tree_internal(git_tree_cache **out,
			      const char **buffer_in, const char *buffer_end,
			      git_pool *pool)
{
	git_tree_cache *tree = NULL;
	const char *name_start, *buffer;
	int count;

	buffer = name_start = *buffer_in;

	if ((buffer = memchr(buffer, '\0', buffer_end - buffer)) == NULL)
		goto corrupted;

	if (++buffer >= buffer_end)
		goto corrupted;

	if (git_tree_cache_new(&tree, name_start, pool) < 0)
		return -1;

	/* Blank-terminated ASCII decimal number of entries in this tree */
	if (git__strntol32(&count, buffer, buffer_end - buffer, &buffer, 10) < 0)
		goto corrupted;

	tree->entry_count = count;

	if (*buffer != ' ' || ++buffer >= buffer_end)
		goto corrupted;

	 /* Number of children of the tree, newline-terminated */
	if (git__strntol32(&count, buffer, buffer_end - buffer, &buffer, 10) < 0 || count < 0)
		goto corrupted;

	tree->children_count = count;

	if (*buffer != '\n' || ++buffer > buffer_end)
		goto corrupted;

	/* The SHA1 is only there if it's not invalidated */
	if (tree->entry_count >= 0) {
		/* 160-bit SHA-1 for this tree and it's children */
		if (buffer + GIT_OID_RAWSZ > buffer_end)
			goto corrupted;

		git_oid_fromraw(&tree->oid, (const unsigned char *)buffer);
		buffer += GIT_OID_RAWSZ;
	}

	/* Parse children: */
	if (tree->children_count > 0) {
		size_t i, bufsize;

		GIT_ERROR_CHECK_ALLOC_MULTIPLY(&bufsize, tree->children_count, sizeof(git_tree_cache*));

		tree->children = git_pool_malloc(pool, bufsize);
		GIT_ERROR_CHECK_ALLOC(tree->children);

		memset(tree->children, 0x0, bufsize);

		for (i = 0; i < tree->children_count; ++i) {
			if (read_tree_internal(&tree->children[i], &buffer, buffer_end, pool) < 0)
				goto corrupted;
		}
	}

	*buffer_in = buffer;
	*out = tree;
	return 0;

 corrupted:
	git_error_set(GIT_ERROR_INDEX, "corrupted TREE extension in index");
	return -1;
}