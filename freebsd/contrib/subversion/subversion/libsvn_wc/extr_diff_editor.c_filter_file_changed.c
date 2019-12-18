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
struct filter_tree_baton_t {TYPE_2__* processor; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* file_changed ) (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void*,TYPE_2__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void*,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
filter_file_changed(const char *relpath,
                    const svn_diff_source_t *left_source,
                    const svn_diff_source_t *right_source,
                    const char *left_file,
                    const char *right_file,
                    /*const*/ apr_hash_t *left_props,
                    /*const*/ apr_hash_t *right_props,
                    svn_boolean_t file_modified,
                    const apr_array_header_t *prop_changes,
                    void *file_baton,
                    const svn_diff_tree_processor_t *processor,
                    apr_pool_t *scratch_pool)
{
  struct filter_tree_baton_t *fb = processor->baton;

  SVN_ERR(fb->processor->file_changed(relpath,
                                      left_source,
                                      right_source,
                                      left_file,
                                      right_file,
                                      left_props,
                                      right_props,
                                      file_modified,
                                      prop_changes,
                                      file_baton,
                                      fb->processor,
                                      scratch_pool));
  return SVN_NO_ERROR;
}