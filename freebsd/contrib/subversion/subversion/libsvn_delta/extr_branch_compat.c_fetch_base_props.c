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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  (* svn_branch__compat_fetch_func_t ) (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
struct TYPE_3__ {scalar_t__ action; char* copyfrom_path; int /*<<< orphan*/  changing_rev; int /*<<< orphan*/  copyfrom_rev; } ;
typedef  TYPE_1__ change_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 scalar_t__ RESTRUCTURE_ADD ; 
 scalar_t__ RESTRUCTURE_DELETE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 char* find_enclosing_copy (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 char* svn_relpath_join (char*,char const*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_skip_ancestor (char const*,char const*) ; 

__attribute__((used)) static svn_error_t *
fetch_base_props(apr_hash_t **base_props,
                 apr_hash_t *changes,
                 const char *repos_relpath,
                 svn_branch__compat_fetch_func_t fetch_func,
                 void *fetch_baton,
                 apr_pool_t *result_pool,
                 apr_pool_t *scratch_pool)
{
  const change_node_t *change = svn_hash_gets(changes, repos_relpath);
  const char *source_path = NULL;
  svn_revnum_t source_rev;

  if (change->action == RESTRUCTURE_DELETE)
    {
      *base_props = NULL;
    }

  else if (change->action == RESTRUCTURE_ADD && ! change->copyfrom_path)
    {
      *base_props = apr_hash_make(result_pool);
    }
  else if (change->copyfrom_path)
    {
      source_path = change->copyfrom_path;
      source_rev = change->copyfrom_rev;
    }
  else /* RESTRUCTURE_NONE */
    {
      /* It's an edit, but possibly to a copy child. Discover if it's a
         copy child, & find the copy-from source. */

      const char *copy_path
        = find_enclosing_copy(changes, repos_relpath, scratch_pool);

      if (copy_path)
        {
          const change_node_t *enclosing_copy
            = svn_hash_gets(changes, copy_path);
          const char *remainder
            = svn_relpath_skip_ancestor(copy_path, repos_relpath);

          source_path = svn_relpath_join(enclosing_copy->copyfrom_path,
                                         remainder, scratch_pool);
          source_rev = enclosing_copy->copyfrom_rev;
        }
      else
        {
          /* It's a plain edit (not a copy child path). */
          source_path = repos_relpath;
          source_rev = change->changing_rev;
        }
    }

  if (source_path)
    {
      SVN_ERR(fetch_func(NULL, base_props, NULL, NULL,
                         fetch_baton, source_path, source_rev,
                         result_pool, scratch_pool));
    }

  return SVN_NO_ERROR;
}