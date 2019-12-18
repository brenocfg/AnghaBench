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
typedef  int /*<<< orphan*/  svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_info_receiver_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
struct TYPE_4__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
struct info_to_relpath_baton {char const* anchor_relpath; char const* anchor_abspath; int /*<<< orphan*/  wc_ctx; void* info_baton; int /*<<< orphan*/  info_receiver; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  info_receiver_relpath_wrapper ; 
 int /*<<< orphan*/  svn_client_info3 (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,struct info_to_relpath_baton*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_path_is_url (char const*) ; 

svn_error_t *
svn_client_info2(const char *path_or_url,
                 const svn_opt_revision_t *peg_revision,
                 const svn_opt_revision_t *revision,
                 svn_info_receiver_t receiver,
                 void *receiver_baton,
                 svn_depth_t depth,
                 const apr_array_header_t *changelists,
                 svn_client_ctx_t *ctx,
                 apr_pool_t *pool)
{
  struct info_to_relpath_baton rb;
  const char *abspath_or_url = path_or_url;

  rb.anchor_relpath = NULL;
  rb.info_receiver = receiver;
  rb.info_baton = receiver_baton;
  rb.wc_ctx = ctx->wc_ctx;

  if (!svn_path_is_url(path_or_url))
    {
      SVN_ERR(svn_dirent_get_absolute(&abspath_or_url, path_or_url, pool));
      rb.anchor_abspath = abspath_or_url;
      rb.anchor_relpath = path_or_url;
    }

  SVN_ERR(svn_client_info3(abspath_or_url,
                           peg_revision,
                           revision,
                           depth,
                           FALSE, TRUE,
                           changelists,
                           info_receiver_relpath_wrapper,
                           &rb,
                           ctx,
                           pool));

  return SVN_NO_ERROR;
}