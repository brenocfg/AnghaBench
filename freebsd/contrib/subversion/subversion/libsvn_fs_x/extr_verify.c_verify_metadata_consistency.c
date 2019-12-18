#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
struct TYPE_12__ {scalar_t__ max_files_per_dir; int /*<<< orphan*/  min_unpacked_rev; } ;
typedef  TYPE_1__ svn_fs_x__data_t ;
struct TYPE_13__ {TYPE_1__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  (* svn_fs_progress_notify_func_t ) (scalar_t__,void*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * compare_l2p_to_p2l_index (TYPE_2__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * compare_p2l_to_l2p_index (TYPE_2__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * compare_p2l_to_rev (TYPE_2__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_fs_x__pack_size (TYPE_2__*,scalar_t__) ; 
 scalar_t__ svn_fs_x__packed_base_rev (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/ * svn_fs_x__read_min_unpacked_rev (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * verify_index_checksums (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * verify_revprops (TYPE_2__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
verify_metadata_consistency(svn_fs_t *fs,
                            svn_revnum_t start,
                            svn_revnum_t end,
                            svn_fs_progress_notify_func_t notify_func,
                            void *notify_baton,
                            svn_cancel_func_t cancel_func,
                            void *cancel_baton,
                            apr_pool_t *scratch_pool)
{
  svn_error_t *err;
  svn_fs_x__data_t *ffd = fs->fsap_data;
  svn_revnum_t revision, next_revision;
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);

  for (revision = start; revision <= end; revision = next_revision)
    {
      svn_revnum_t count = svn_fs_x__packed_base_rev(fs, revision);
      svn_revnum_t pack_start = count;
      svn_revnum_t pack_end = pack_start + svn_fs_x__pack_size(fs, revision);

      svn_pool_clear(iterpool);

      if (notify_func && (pack_start % ffd->max_files_per_dir == 0))
        notify_func(pack_start, notify_baton, iterpool);

      /* Check for external corruption to the indexes. */
      err = verify_index_checksums(fs, pack_start, cancel_func,
                                   cancel_baton, iterpool);

      /* two-way index check */
      if (!err)
        err = compare_l2p_to_p2l_index(fs, pack_start, pack_end - pack_start,
                                       cancel_func, cancel_baton, iterpool);
      if (!err)
        err = compare_p2l_to_l2p_index(fs, pack_start, pack_end - pack_start,
                                       cancel_func, cancel_baton, iterpool);

      /* verify in-index checksums and types vs. actual rev / pack files */
      if (!err)
        err = compare_p2l_to_rev(fs, pack_start, pack_end - pack_start,
                                 cancel_func, cancel_baton, iterpool);

      /* ensure that revprops are available and accessible */
      if (!err)
        err = verify_revprops(fs, pack_start, pack_end,
                              cancel_func, cancel_baton, iterpool);

      /* concurrent packing is one of the reasons why verification may fail.
         Make sure, we operate on up-to-date information. */
      if (err)
        {
          svn_error_t *err2
            = svn_fs_x__read_min_unpacked_rev(&ffd->min_unpacked_rev,
                                              fs, scratch_pool);

          /* Be careful to not leak ERR. */
          if (err2)
            return svn_error_trace(svn_error_compose_create(err, err2));
        }

      /* retry the whole shard if it got packed in the meantime */
      if (err && count != svn_fs_x__pack_size(fs, revision))
        {
          svn_error_clear(err);

          /* We could simply assign revision here but the code below is
             more intuitive to maintainers. */
          next_revision = svn_fs_x__packed_base_rev(fs, revision);
        }
      else
        {
          SVN_ERR(err);
          next_revision = pack_end;
        }
    }

  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}