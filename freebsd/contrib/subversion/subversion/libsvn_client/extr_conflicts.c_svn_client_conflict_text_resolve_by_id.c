#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
struct TYPE_5__ {int /*<<< orphan*/  local_abspath; } ;
typedef  TYPE_1__ svn_client_conflict_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_option_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_option_id_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CLIENT_CONFLICT_OPTION_NOT_APPLICABLE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_client_conflict_option_find_by_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_client_conflict_text_get_resolution_options (int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_text_resolve (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_client_conflict_text_resolve_by_id(
  svn_client_conflict_t *conflict,
  svn_client_conflict_option_id_t option_id,
  svn_client_ctx_t *ctx,
  apr_pool_t *scratch_pool)
{
  apr_array_header_t *resolution_options;
  svn_client_conflict_option_t *option;

  SVN_ERR(svn_client_conflict_text_get_resolution_options(
            &resolution_options, conflict, ctx,
            scratch_pool, scratch_pool));
  option = svn_client_conflict_option_find_by_id(resolution_options,
                                                 option_id);
  if (option == NULL)
    return svn_error_createf(SVN_ERR_CLIENT_CONFLICT_OPTION_NOT_APPLICABLE,
                             NULL,
                             _("Inapplicable conflict resolution option "
                               "given for conflicted path '%s'"),
                             svn_dirent_local_style(conflict->local_abspath,
                                                    scratch_pool));

  SVN_ERR(svn_client_conflict_text_resolve(conflict, option, ctx, scratch_pool));

  return SVN_NO_ERROR;
}