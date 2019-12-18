#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {struct filter_tree_baton_t* baton; } ;
typedef  TYPE_1__ svn_diff_tree_processor_t ;
typedef  int /*<<< orphan*/  svn_diff_source_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct filter_tree_baton_t {TYPE_2__* processor; int /*<<< orphan*/  changelist_hash; int /*<<< orphan*/  wc_ctx; int /*<<< orphan*/  root_local_abspath; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* file_opened ) (void**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,void*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  stub1 (void**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,void*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__changelist_match (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
filter_file_opened(void **new_file_baton,
                   svn_boolean_t *skip,
                   const char *relpath,
                   const svn_diff_source_t *left_source,
                   const svn_diff_source_t *right_source,
                   const svn_diff_source_t *copyfrom_source,
                   void *dir_baton,
                   const svn_diff_tree_processor_t *processor,
                   apr_pool_t *result_pool,
                   apr_pool_t *scratch_pool)
{
  struct filter_tree_baton_t *fb = processor->baton;
  const char *local_abspath
    = svn_dirent_join(fb->root_local_abspath, relpath, scratch_pool);

  /* Skip if not a member of a given changelist */
  if (! svn_wc__changelist_match(fb->wc_ctx, local_abspath,
                                 fb->changelist_hash, scratch_pool))
    {
      *skip = TRUE;
      return SVN_NO_ERROR;
    }

  SVN_ERR(fb->processor->file_opened(new_file_baton,
                                     skip,
                                     relpath,
                                     left_source,
                                     right_source,
                                     copyfrom_source,
                                     dir_baton,
                                     fb->processor,
                                     result_pool,
                                     scratch_pool));
  return SVN_NO_ERROR;
}