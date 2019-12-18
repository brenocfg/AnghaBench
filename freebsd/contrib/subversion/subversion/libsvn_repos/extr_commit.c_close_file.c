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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
struct file_baton {int /*<<< orphan*/  path; TYPE_1__* edit_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/  txn_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_checksum_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/ * svn_checksum_mismatch_err (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_parse_hex (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_file_checksum (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
close_file(void *file_baton,
           const char *text_digest,
           apr_pool_t *pool)
{
  struct file_baton *fb = file_baton;

  if (text_digest)
    {
      svn_checksum_t *checksum;
      svn_checksum_t *text_checksum;

      SVN_ERR(svn_fs_file_checksum(&checksum, svn_checksum_md5,
                                   fb->edit_baton->txn_root, fb->path,
                                   TRUE, pool));
      SVN_ERR(svn_checksum_parse_hex(&text_checksum, svn_checksum_md5,
                                     text_digest, pool));

      if (!svn_checksum_match(text_checksum, checksum))
        return svn_checksum_mismatch_err(text_checksum, checksum, pool,
                            _("Checksum mismatch for resulting fulltext\n(%s)"),
                            fb->path);
    }

  return SVN_NO_ERROR;
}