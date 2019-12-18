#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ len; } ;
typedef  TYPE_2__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_15__ {scalar_t__ offset; scalar_t__ end; scalar_t__ changes_len; int /*<<< orphan*/  revision; TYPE_1__* rev_file; } ;
typedef  TYPE_3__ revision_info_t ;
typedef  int /*<<< orphan*/  query_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_off_t ;
struct TYPE_13__ {int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SET ; 
 scalar_t__ MAX (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_phys_change_count (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_noderev (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_phsy_noderev (TYPE_2__**,int /*<<< orphan*/ *,scalar_t__,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__parse_revision_trailer (scalar_t__*,scalar_t__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_fs_fs__unparse_revision_trailer (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_read_full2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_stringbuf_ncreate (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_phys_revision(query_t *query,
                   revision_info_t *info,
                   apr_pool_t *result_pool,
                   apr_pool_t *scratch_pool)
{
  char buf[64];
  apr_off_t root_node_offset;
  apr_off_t changes_offset;
  svn_stringbuf_t *trailer;
  svn_stringbuf_t *noderev_str;

  /* Read the last 64 bytes of the revision (if long enough). */
  apr_off_t start = MAX(info->offset, info->end - sizeof(buf));
  apr_size_t len = (apr_size_t)(info->end - start);
  SVN_ERR(svn_io_file_seek(info->rev_file->file, APR_SET, &start,
                           scratch_pool));
  SVN_ERR(svn_io_file_read_full2(info->rev_file->file, buf, len, NULL, NULL,
                                 scratch_pool));
  trailer = svn_stringbuf_ncreate(buf, len, scratch_pool);

  /* Parse that trailer. */
  SVN_ERR(svn_fs_fs__parse_revision_trailer(&root_node_offset,
                                            &changes_offset, trailer,
                                            info->revision));
  SVN_ERR(get_phys_change_count(query, info, scratch_pool));

  /* Calculate the length of the changes list. */
  trailer = svn_fs_fs__unparse_revision_trailer(root_node_offset,
                                                changes_offset,
                                                scratch_pool);
  info->changes_len = info->end - info->offset - changes_offset
                    - trailer->len;

  /* Recursively read nodes added in this rev. */
  SVN_ERR(read_phsy_noderev(&noderev_str, query, root_node_offset, info,
                            scratch_pool, scratch_pool));
  SVN_ERR(read_noderev(query, noderev_str, info, result_pool, scratch_pool));

  return SVN_NO_ERROR;
}