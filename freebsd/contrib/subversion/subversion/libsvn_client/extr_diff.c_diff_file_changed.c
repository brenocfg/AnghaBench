#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {int /*<<< orphan*/  revision; } ;
typedef  TYPE_1__ svn_diff_source_t ;
typedef  scalar_t__ svn_boolean_t ;
struct svn_diff_tree_processor_t {int /*<<< orphan*/ * baton; } ;
typedef  int /*<<< orphan*/  diff_writer_info_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_8__ {scalar_t__ nelts; } ;
typedef  TYPE_2__ apr_array_header_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  diff_content_changed (scalar_t__*,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diff_props_changed (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff_op_modified ; 

__attribute__((used)) static svn_error_t *
diff_file_changed(const char *relpath,
                  const svn_diff_source_t *left_source,
                  const svn_diff_source_t *right_source,
                  const char *left_file,
                  const char *right_file,
                  /*const*/ apr_hash_t *left_props,
                  /*const*/ apr_hash_t *right_props,
                  svn_boolean_t file_modified,
                  const apr_array_header_t *prop_changes,
                  void *file_baton,
                  const struct svn_diff_tree_processor_t *processor,
                  apr_pool_t *scratch_pool)
{
  diff_writer_info_t *dwi = processor->baton;
  svn_boolean_t wrote_header = FALSE;

  if (file_modified)
    SVN_ERR(diff_content_changed(&wrote_header, relpath,
                                 left_file, right_file,
                                 left_source->revision,
                                 right_source->revision,
                                 left_props, right_props,
                                 svn_diff_op_modified, FALSE,
                                 NULL,
                                 SVN_INVALID_REVNUM, dwi,
                                 scratch_pool));
  if (prop_changes->nelts > 0)
    SVN_ERR(diff_props_changed(relpath,
                               left_source->revision,
                               right_source->revision, prop_changes,
                               left_props, right_props, !wrote_header,
                               dwi, scratch_pool));
  return SVN_NO_ERROR;
}