#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
struct TYPE_27__ {TYPE_6__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
struct TYPE_28__ {int /*<<< orphan*/  stream; } ;
typedef  TYPE_2__ svn_fs_fs__revision_file_t ;
struct TYPE_29__ {int /*<<< orphan*/  number; int /*<<< orphan*/  revision; } ;
typedef  TYPE_3__ svn_fs_fs__id_part_t ;
struct TYPE_30__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_4__ svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_31__ {int /*<<< orphan*/  second; int /*<<< orphan*/  revision; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_5__ pair_cache_key_t ;
typedef  int /*<<< orphan*/  node_revision_t ;
struct TYPE_32__ {scalar_t__ node_revision_cache; } ;
typedef  TYPE_6__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int APR_BUFFERED ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int APR_READ ; 
 scalar_t__ APR_STATUS_IS_ENOENT (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 TYPE_4__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  block_read (void**,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* err_dangling_id (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fixup_node_revision (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_and_seek_revision (TYPE_2__**,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__get (void**,scalar_t__*,scalar_t__,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__set (scalar_t__,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_4__*) ; 
 TYPE_4__* svn_error_trace (TYPE_4__*) ; 
 int /*<<< orphan*/  svn_fs_fs__close_revision_file (TYPE_2__*) ; 
 scalar_t__ svn_fs_fs__id_is_txn (int /*<<< orphan*/  const*) ; 
 TYPE_3__* svn_fs_fs__id_rev_item (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svn_fs_fs__path_txn_node_rev (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__read_noderev (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_io_file_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_from_aprfile2 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ use_block_read (TYPE_1__*) ; 

__attribute__((used)) static svn_error_t *
get_node_revision_body(node_revision_t **noderev_p,
                       svn_fs_t *fs,
                       const svn_fs_id_t *id,
                       apr_pool_t *result_pool,
                       apr_pool_t *scratch_pool)
{
  svn_error_t *err;
  svn_boolean_t is_cached = FALSE;
  fs_fs_data_t *ffd = fs->fsap_data;

  if (svn_fs_fs__id_is_txn(id))
    {
      apr_file_t *file;

      /* This is a transaction node-rev.  Its storage logic is very
         different from that of rev / pack files. */
      err = svn_io_file_open(&file,
                             svn_fs_fs__path_txn_node_rev(fs, id,
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

      SVN_ERR(svn_fs_fs__read_noderev(noderev_p,
                                      svn_stream_from_aprfile2(file,
                                                               FALSE,
                                                               scratch_pool),
                                      result_pool, scratch_pool));
    }
  else
    {
      svn_fs_fs__revision_file_t *revision_file;

      /* noderevs in rev / pack files can be cached */
      const svn_fs_fs__id_part_t *rev_item = svn_fs_fs__id_rev_item(id);
      pair_cache_key_t key = { 0 };
      key.revision = rev_item->revision;
      key.second = rev_item->number;

      /* Not found or not applicable. Try a noderev cache lookup.
       * If that succeeds, we are done here. */
      if (ffd->node_revision_cache)
        {
          SVN_ERR(svn_cache__get((void **) noderev_p,
                                 &is_cached,
                                 ffd->node_revision_cache,
                                 &key,
                                 result_pool));
          if (is_cached)
            return SVN_NO_ERROR;
        }

      /* read the data from disk */
      SVN_ERR(open_and_seek_revision(&revision_file, fs,
                                     rev_item->revision,
                                     rev_item->number,
                                     scratch_pool));

      if (use_block_read(fs))
        {
          /* block-read will parse the whole block and will also return
             the one noderev that we need right now. */
          SVN_ERR(block_read((void **)noderev_p, fs,
                             rev_item->revision,
                             rev_item->number,
                             revision_file,
                             result_pool,
                             scratch_pool));
        }
      else
        {
          /* physical addressing mode reading, parsing and caching */
          SVN_ERR(svn_fs_fs__read_noderev(noderev_p,
                                          revision_file->stream,
                                          result_pool,
                                          scratch_pool));
          SVN_ERR(fixup_node_revision(fs, *noderev_p, scratch_pool));

          /* The noderev is not in cache, yet. Add it, if caching has been enabled. */
          if (ffd->node_revision_cache)
            SVN_ERR(svn_cache__set(ffd->node_revision_cache,
                                   &key,
                                   *noderev_p,
                                   scratch_pool));
        }

      SVN_ERR(svn_fs_fs__close_revision_file(revision_file));
    }

  return SVN_NO_ERROR;
}