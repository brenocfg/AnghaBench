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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {scalar_t__ kind; } ;
typedef  TYPE_1__ svn_checksum_t ;
struct editor_baton {int /*<<< orphan*/  edit_pool; int /*<<< orphan*/  changes; } ;
struct change_node {char const* contents_abspath; int /*<<< orphan*/  checksum; int /*<<< orphan*/  contents_changed; int /*<<< orphan*/  props; int /*<<< orphan*/  deleting; int /*<<< orphan*/  kind; int /*<<< orphan*/  action; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  RESTRUCTURE_ADD ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 struct change_node* insert_change (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_dup (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_checksum_md5 ; 
 int /*<<< orphan*/  svn_io_file_del_on_pool_cleanup ; 
 int /*<<< orphan*/  svn_node_file ; 
 int /*<<< orphan*/  svn_prop_hash_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_stream_checksummed2 (int /*<<< orphan*/ *,TYPE_1__**,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_copy3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_unique (int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
add_file_cb(void *baton,
            const char *relpath,
            const svn_checksum_t *checksum,
            svn_stream_t *contents,
            apr_hash_t *props,
            svn_revnum_t replaces_rev,
            apr_pool_t *scratch_pool)
{
  struct editor_baton *eb = baton;
  const char *tmp_filename;
  svn_stream_t *tmp_stream;
  svn_checksum_t *md5_checksum;
  struct change_node *change = insert_change(relpath, eb->changes);

  /* We may need to re-checksum these contents */
  if (!(checksum && checksum->kind == svn_checksum_md5))
    contents = svn_stream_checksummed2(contents, &md5_checksum, NULL,
                                       svn_checksum_md5, TRUE, scratch_pool);
  else
    md5_checksum = (svn_checksum_t *)checksum;

  /* Spool the contents to a tempfile, and provide that to the driver. */
  SVN_ERR(svn_stream_open_unique(&tmp_stream, &tmp_filename, NULL,
                                 svn_io_file_del_on_pool_cleanup,
                                 eb->edit_pool, scratch_pool));
  SVN_ERR(svn_stream_copy3(contents, tmp_stream, NULL, NULL, scratch_pool));

  change->action = RESTRUCTURE_ADD;
  change->kind = svn_node_file;
  change->deleting = replaces_rev;
  change->props = svn_prop_hash_dup(props, eb->edit_pool);
  change->contents_changed = TRUE;
  change->contents_abspath = tmp_filename;
  change->checksum = svn_checksum_dup(md5_checksum, eb->edit_pool);

  return SVN_NO_ERROR;
}