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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_4__ {scalar_t__ is_packed; } ;
typedef  TYPE_1__ svn_fs_fs__revision_file_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  l2p_index_lookup (scalar_t__*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2p_proto_index_lookup (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__get_packed_offset (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_fs__use_log_addressing (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__item_offset(apr_off_t *absolute_position,
                       svn_fs_t *fs,
                       svn_fs_fs__revision_file_t *rev_file,
                       svn_revnum_t revision,
                       const svn_fs_fs__id_part_t *txn_id,
                       apr_uint64_t item_index,
                       apr_pool_t *scratch_pool)
{
  svn_error_t *err = SVN_NO_ERROR;
  if (txn_id)
    {
      if (svn_fs_fs__use_log_addressing(fs))
        {
          /* the txn is going to produce a rev with logical addressing.
             So, we need to get our info from the (proto) index file. */
          SVN_ERR(l2p_proto_index_lookup(absolute_position, fs, txn_id,
                                         item_index, scratch_pool));
        }
      else
        {
          /* for data in txns, item_index *is* the offset */
          *absolute_position = item_index;
        }
    }
  else if (svn_fs_fs__use_log_addressing(fs))
    {
      /* ordinary index lookup */
      SVN_ERR(l2p_index_lookup(absolute_position, fs, rev_file, revision,
                               item_index, scratch_pool));
    }
  else if (rev_file->is_packed)
    {
      /* pack file with physical addressing */
      apr_off_t rev_offset;
      SVN_ERR(svn_fs_fs__get_packed_offset(&rev_offset, fs, revision,
                                           scratch_pool));
      *absolute_position = rev_offset + item_index;
    }
  else
    {
      /* for non-packed revs with physical addressing,
         item_index *is* the offset */
      *absolute_position = item_index;
    }

  return svn_error_trace(err);
}