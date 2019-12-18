#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  fetch_baton; int /*<<< orphan*/  (* fetch_func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ wrap_fetch_baton_t ;
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_dir ; 

__attribute__((used)) static svn_error_t *
wrap_fetch_func(svn_node_kind_t *kind,
                apr_hash_t **props,
                svn_stringbuf_t **file_text,
                apr_hash_t **children_names,
                void *baton,
                const char *repos_relpath,
                svn_revnum_t revision,
                apr_pool_t *result_pool,
                apr_pool_t *scratch_pool)
{
  wrap_fetch_baton_t *b = baton;

  if (revision == 0 && strcmp(repos_relpath, "top0") == 0)
    {
      if (kind)
        *kind = svn_node_dir;
      if (props)
        *props = apr_hash_make(result_pool);
      if (file_text)
        *file_text = NULL;
      if (children_names)
        *children_names = apr_hash_make(result_pool);
    }
  else
    {
      SVN_ERR(b->fetch_func(kind, props, file_text, children_names,
                            b->fetch_baton,
                            repos_relpath, revision,
                            result_pool, scratch_pool));
    }

  return SVN_NO_ERROR;
}