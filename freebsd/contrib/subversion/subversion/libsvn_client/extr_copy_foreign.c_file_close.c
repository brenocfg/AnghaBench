#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
struct file_baton_t {int /*<<< orphan*/  pool; int /*<<< orphan*/  properties; int /*<<< orphan*/  local_abspath; int /*<<< orphan*/  digest; struct dir_baton_t* pb; struct edit_baton_t* eb; } ;
struct edit_baton_t {int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  notify_func; int /*<<< orphan*/  wc_ctx; } ;
struct dir_baton_t {int dummy; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  ensure_added (struct dir_baton_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maybe_done (struct dir_baton_t*) ; 
 int /*<<< orphan*/ * svn_checksum__from_digest_md5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/  svn_checksum_mismatch_err (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_parse_hex (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_dirent_local_style (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc_add_from_disk3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
file_close(void *file_baton,
           const char *text_checksum,
           apr_pool_t *scratch_pool)
{
  struct file_baton_t *fb = file_baton;
  struct edit_baton_t *eb = fb->eb;
  struct dir_baton_t *pb = fb->pb;

  SVN_ERR(ensure_added(pb, fb->pool));

  if (text_checksum)
    {
      svn_checksum_t *expected_checksum;
      svn_checksum_t *actual_checksum;

      SVN_ERR(svn_checksum_parse_hex(&expected_checksum, svn_checksum_md5,
                                     text_checksum, fb->pool));
      actual_checksum = svn_checksum__from_digest_md5(fb->digest, fb->pool);

      if (! svn_checksum_match(expected_checksum, actual_checksum))
        return svn_error_trace(
                    svn_checksum_mismatch_err(expected_checksum,
                                              actual_checksum,
                                              fb->pool,
                                         _("Checksum mismatch for '%s'"),
                                              svn_dirent_local_style(
                                                    fb->local_abspath,
                                                    fb->pool)));
    }

  SVN_ERR(svn_wc_add_from_disk3(eb->wc_ctx, fb->local_abspath, fb->properties,
                                TRUE /* skip checks */,
                                eb->notify_func, eb->notify_baton,
                                fb->pool));

  svn_pool_destroy(fb->pool);
  SVN_ERR(maybe_done(pb));

  return SVN_NO_ERROR;
}