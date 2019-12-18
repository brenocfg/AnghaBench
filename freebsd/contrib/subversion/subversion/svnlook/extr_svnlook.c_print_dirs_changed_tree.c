#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ kind; char action; struct TYPE_3__* sibling; int /*<<< orphan*/  name; struct TYPE_3__* child; scalar_t__ prop_mod; } ;
typedef  TYPE_1__ svn_repos_node_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * check_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_cmdline_printf (int /*<<< orphan*/ *,char*,char const*) ; 
 char* svn_dirent_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
print_dirs_changed_tree(svn_repos_node_t *node,
                        const char *path /* UTF-8! */,
                        apr_pool_t *pool)
{
  svn_repos_node_t *tmp_node;
  svn_boolean_t print_me = FALSE;
  const char *full_path;
  apr_pool_t *iterpool;

  SVN_ERR(check_cancel(NULL));

  if (! node)
    return SVN_NO_ERROR;

  /* Not a directory?  We're not interested. */
  if (node->kind != svn_node_dir)
    return SVN_NO_ERROR;

  /* Got prop mods?  Excellent. */
  if (node->prop_mod)
    print_me = TRUE;

  /* Fly through the list of children, checking for modified files. */
  tmp_node = node->child;
  while (tmp_node && (! print_me))
    {
      if ((tmp_node->kind == svn_node_file)
           || (tmp_node->action == 'A')
           || (tmp_node->action == 'D'))
        {
          print_me = TRUE;
        }
      tmp_node = tmp_node->sibling;
    }

  /* Print the node if it qualifies. */
  if (print_me)
    {
      SVN_ERR(svn_cmdline_printf(pool, "%s/\n", path));
    }

  /* Return here if the node has no children. */
  tmp_node = node->child;
  if (! tmp_node)
    return SVN_NO_ERROR;

  /* Recursively handle the node's children. */
  iterpool = svn_pool_create(pool);
  while (tmp_node)
    {
      svn_pool_clear(iterpool);
      full_path = svn_dirent_join(path, tmp_node->name, iterpool);
      SVN_ERR(print_dirs_changed_tree(tmp_node, full_path, iterpool));
      tmp_node = tmp_node->sibling;
    }
  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}