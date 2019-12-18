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
struct TYPE_3__ {char action; char* copyfrom_path; scalar_t__ kind; char* copyfrom_rev; struct TYPE_3__* sibling; int /*<<< orphan*/  name; struct TYPE_3__* child; scalar_t__ prop_mod; scalar_t__ text_mod; } ;
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
 int /*<<< orphan*/ * svn_cmdline_printf (int /*<<< orphan*/ *,char*,char*,char const*,char*) ; 
 char* svn_dirent_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
print_changed_tree(svn_repos_node_t *node,
                   const char *path /* UTF-8! */,
                   svn_boolean_t copy_info,
                   apr_pool_t *pool)
{
  const char *full_path;
  char status[4] = "_  ";
  svn_boolean_t print_me = TRUE;
  apr_pool_t *iterpool;

  SVN_ERR(check_cancel(NULL));

  if (! node)
    return SVN_NO_ERROR;

  /* Print the node. */
  if (node->action == 'A')
    {
      status[0] = 'A';
      if (copy_info && node->copyfrom_path)
        status[2] = '+';
    }
  else if (node->action == 'D')
    status[0] = 'D';
  else if (node->action == 'R')
    {
      if ((! node->text_mod) && (! node->prop_mod))
        print_me = FALSE;
      if (node->text_mod)
        status[0] = 'U';
      if (node->prop_mod)
        status[1] = 'U';
    }
  else
    print_me = FALSE;

  /* Print this node unless told to skip it. */
  if (print_me)
    {
      SVN_ERR(svn_cmdline_printf(pool, "%s %s%s\n",
                                 status,
                                 path,
                                 node->kind == svn_node_dir ? "/" : ""));
      if (copy_info && node->copyfrom_path)
        /* Remove the leading slash from the copyfrom path for consistency
           with the rest of the output. */
        SVN_ERR(svn_cmdline_printf(pool, "    (from %s%s:r%ld)\n",
                                   (node->copyfrom_path[0] == '/'
                                    ? node->copyfrom_path + 1
                                    : node->copyfrom_path),
                                   (node->kind == svn_node_dir ? "/" : ""),
                                   node->copyfrom_rev));
    }

  /* Return here if the node has no children. */
  node = node->child;
  if (! node)
    return SVN_NO_ERROR;

  /* Recursively handle the node's children. */
  iterpool = svn_pool_create(pool);
  while (node)
    {
      svn_pool_clear(iterpool);
      full_path = svn_dirent_join(path, node->name, iterpool);
      SVN_ERR(print_changed_tree(node, full_path, copy_info, iterpool));
      node = node->sibling;
    }
  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}