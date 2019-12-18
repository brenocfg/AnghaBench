#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_notify_state_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct diff_callbacks_wrapper_baton {int /*<<< orphan*/  baton; TYPE_1__* callbacks; } ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_6__ {scalar_t__ nelts; } ;
typedef  TYPE_2__ apr_array_header_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* props_changed ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* file_changed ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
wrap_3to1_file_changed(svn_wc_adm_access_t *adm_access,
                       svn_wc_notify_state_t *contentstate,
                       svn_wc_notify_state_t *propstate,
                       svn_boolean_t *tree_conflicted,
                       const char *path,
                       const char *tmpfile1,
                       const char *tmpfile2,
                       svn_revnum_t rev1,
                       svn_revnum_t rev2,
                       const char *mimetype1,
                       const char *mimetype2,
                       const apr_array_header_t *propchanges,
                       apr_hash_t *originalprops,
                       void *diff_baton)
{
  struct diff_callbacks_wrapper_baton *b = diff_baton;

  if (tree_conflicted)
    *tree_conflicted = FALSE;

  if (tmpfile2 != NULL)
    SVN_ERR(b->callbacks->file_changed(adm_access, contentstate, path,
                                       tmpfile1, tmpfile2,
                                       rev1, rev2, mimetype1, mimetype2,
                                       b->baton));
  if (propchanges->nelts > 0)
    SVN_ERR(b->callbacks->props_changed(adm_access, propstate, path,
                                        propchanges, originalprops,
                                        b->baton));

  return SVN_NO_ERROR;
}