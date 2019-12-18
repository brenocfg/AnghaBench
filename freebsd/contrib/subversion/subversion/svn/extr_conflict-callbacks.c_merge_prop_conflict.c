#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_t ;
struct TYPE_4__ {int /*<<< orphan*/  ignore_eol_style; } ;
typedef  TYPE_1__ svn_diff_file_options_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_diff_conflict_display_modified_original_latest ; 
 TYPE_1__* svn_diff_file_options_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff_mem_string_diff3 (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff_mem_string_output_merge3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_string_create_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
merge_prop_conflict(svn_stream_t *output,
                    const svn_string_t *base_propval,
                    const svn_string_t *my_propval,
                    const svn_string_t *their_propval,
                    const svn_string_t *merged_propval,
                    svn_cancel_func_t cancel_func,
                    void *cancel_baton,
                    apr_pool_t *pool)
{
  svn_diff_file_options_t *options = svn_diff_file_options_create(pool);
  svn_diff_t *diff;

  /* If any of the property values is missing, use an empty value instead
   * for the purpose of showing a diff. */
  if (base_propval == NULL)
    base_propval = svn_string_create_empty(pool);
  if (my_propval == NULL)
    my_propval = svn_string_create_empty(pool);
  if (their_propval == NULL)
    their_propval = svn_string_create_empty(pool);
    
  options->ignore_eol_style = TRUE;
  SVN_ERR(svn_diff_mem_string_diff3(&diff, base_propval,
                                    merged_propval ?
                                      merged_propval : my_propval,
                                    their_propval, options, pool));
  SVN_ERR(svn_diff_mem_string_output_merge3(
            output, diff, base_propval,
            merged_propval ? merged_propval : my_propval, their_propval,
            _("||||||| ORIGINAL"),
            _("<<<<<<< MINE"),
            _(">>>>>>> THEIRS"),
            "=======",
            svn_diff_conflict_display_modified_original_latest,
            cancel_func,
            cancel_baton,
            pool));

  return SVN_NO_ERROR;
}