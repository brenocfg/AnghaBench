#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_x__revision_file_t ;
struct TYPE_28__ {int /*<<< orphan*/  second; int /*<<< orphan*/  revision; } ;
typedef  TYPE_1__ svn_fs_x__pair_cache_key_t ;
typedef  int /*<<< orphan*/  svn_fs_x__noderev_t ;
struct TYPE_29__ {int /*<<< orphan*/  number; int /*<<< orphan*/  change_set; } ;
typedef  TYPE_2__ svn_fs_x__id_t ;
struct TYPE_30__ {int /*<<< orphan*/  node_revision_cache; scalar_t__ noderevs_container_cache; } ;
typedef  TYPE_3__ svn_fs_x__data_t ;
struct TYPE_31__ {TYPE_3__* fsap_data; } ;
typedef  TYPE_4__ svn_fs_t ;
struct TYPE_32__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_5__ svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int APR_BUFFERED ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int APR_READ ; 
 scalar_t__ APR_STATUS_IS_ENOENT (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 TYPE_5__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  block_read (void**,TYPE_4__*,TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* err_dangling_id (TYPE_4__*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  svn_cache__get (void**,scalar_t__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__get_partial (void**,scalar_t__*,scalar_t__,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_5__*) ; 
 TYPE_5__* svn_error_trace (TYPE_5__*) ; 
 int /*<<< orphan*/  svn_fs_x__close_revision_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__get_revnum (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_fs_x__is_packed_rev (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_fs_x__is_txn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__item_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__noderevs_get_func ; 
 int /*<<< orphan*/  svn_fs_x__packed_base_rev (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__path_txn_node_rev (TYPE_4__*,TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__read_noderev (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__rev_file_init (int /*<<< orphan*/ **,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_5__* svn_io_file_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_from_aprfile2 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_node_revision_body(svn_fs_x__noderev_t **noderev_p,
                       svn_fs_t *fs,
                       const svn_fs_x__id_t *id,
                       apr_pool_t *result_pool,
                       apr_pool_t *scratch_pool)
{
  svn_error_t *err;
  svn_boolean_t is_cached = FALSE;
  svn_fs_x__data_t *ffd = fs->fsap_data;

  if (svn_fs_x__is_txn(id->change_set))
    {
      apr_file_t *file;
      svn_stream_t *stream;

      /* This is a transaction node-rev.  Its storage logic is very
         different from that of rev / pack files. */
      err = svn_io_file_open(&file,
                             svn_fs_x__path_txn_node_rev(fs, id,
                                                         scratch_pool,
                                                         scratch_pool),
                             APR_READ | APR_BUFFERED, APR_OS_DEFAULT,
                             scratch_pool);
      if (err && APR_STATUS_IS_ENOENT(err->apr_err))
        {
          svn_error_clear(err);
          return svn_error_trace(err_dangling_id(fs, id));
        }
      else if (err)
        {
          return svn_error_trace(err);
        }

      /* Be sure to close the file ASAP. */
      stream = svn_stream_from_aprfile2(file, FALSE, scratch_pool);
      SVN_ERR(svn_fs_x__read_noderev(noderev_p, stream,
                                     result_pool, scratch_pool));
    }
  else
    {
      svn_fs_x__revision_file_t *revision_file;

      /* noderevs in rev / pack files can be cached */
      svn_revnum_t revision = svn_fs_x__get_revnum(id->change_set);
      svn_fs_x__pair_cache_key_t key;

      SVN_ERR(svn_fs_x__rev_file_init(&revision_file, fs, revision,
                                      scratch_pool));

      /* First, try a noderevs container cache lookup. */
      if (   svn_fs_x__is_packed_rev(fs, revision)
          && ffd->noderevs_container_cache)
        {
          apr_off_t offset;
          apr_uint32_t sub_item;
          SVN_ERR(svn_fs_x__item_offset(&offset, &sub_item, fs, revision_file,
                                        id, scratch_pool));
          key.revision = svn_fs_x__packed_base_rev(fs, revision);
          key.second = offset;

          SVN_ERR(svn_cache__get_partial((void **)noderev_p, &is_cached,
                                         ffd->noderevs_container_cache, &key,
                                         svn_fs_x__noderevs_get_func,
                                         &sub_item, result_pool));
          if (is_cached)
            return SVN_NO_ERROR;
        }

      key.revision = revision;
      key.second = id->number;

      /* Not found or not applicable. Try a noderev cache lookup.
       * If that succeeds, we are done here. */
      SVN_ERR(svn_cache__get((void **) noderev_p,
                             &is_cached,
                             ffd->node_revision_cache,
                             &key,
                             result_pool));
      if (is_cached)
        return SVN_NO_ERROR;

      /* block-read will parse the whole block and will also return
         the one noderev that we need right now. */
      SVN_ERR(block_read((void **)noderev_p, fs,
                         id,
                         revision_file,
                         NULL,
                         result_pool,
                         scratch_pool));
      SVN_ERR(svn_fs_x__close_revision_file(revision_file));
    }

  return SVN_NO_ERROR;
}