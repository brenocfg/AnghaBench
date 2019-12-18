#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree_entry ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb ;
struct TYPE_6__ {char const* path; int /*<<< orphan*/  id; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_7__ {int /*<<< orphan*/  local; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CLONE_NO_LOCAL ; 
 int /*<<< orphan*/  GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_path_url (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 TYPE_4__ g_options ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  git_index_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_index_write_tree_to (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_odb (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_entry_bypath (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_tree_entry_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void test_clone_nonetwork__clone_tag_to_tree(void)
{
	git_repository *stage;
	git_index_entry entry;
	git_index *index;
	git_odb *odb;
	git_oid tree_id;
	git_tree *tree;
	git_reference *tag;
	git_tree_entry *tentry;
	const char *file_path = "some/deep/path.txt";
	const char *file_content = "some content\n";
	const char *tag_name = "refs/tags/tree-tag";

	stage = cl_git_sandbox_init("testrepo.git");
	cl_git_pass(git_repository_odb(&odb, stage));
	cl_git_pass(git_index_new(&index));

	memset(&entry, 0, sizeof(git_index_entry));
	entry.path = file_path;
	entry.mode = GIT_FILEMODE_BLOB;
	cl_git_pass(git_odb_write(&entry.id, odb, file_content, strlen(file_content), GIT_OBJECT_BLOB));

	cl_git_pass(git_index_add(index, &entry));
	cl_git_pass(git_index_write_tree_to(&tree_id, index, stage));
	cl_git_pass(git_reference_create(&tag, stage, tag_name, &tree_id, 0, NULL));
	git_reference_free(tag);
	git_odb_free(odb);
	git_index_free(index);

	g_options.local = GIT_CLONE_NO_LOCAL;
	cl_git_pass(git_clone(&g_repo, cl_git_path_url(git_repository_path(stage)), "./foo", &g_options));
	git_repository_free(stage);

	cl_git_pass(git_reference_lookup(&tag, g_repo, tag_name));
	cl_git_pass(git_tree_lookup(&tree, g_repo, git_reference_target(tag)));
	git_reference_free(tag);

	cl_git_pass(git_tree_entry_bypath(&tentry, tree, file_path));
	git_tree_entry_free(tentry);
	git_tree_free(tree);

	cl_fixture_cleanup("testrepo.git");
}