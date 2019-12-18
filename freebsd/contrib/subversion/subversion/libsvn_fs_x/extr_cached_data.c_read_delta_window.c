#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_9__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_txdelta_window_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_fs_x__revision_file_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
struct TYPE_11__ {int /*<<< orphan*/  change_set; } ;
struct TYPE_10__ {int chunk_index; scalar_t__ start; scalar_t__ current; scalar_t__ size; int /*<<< orphan*/  ver; TYPE_5__ rep_id; TYPE_9__* sfile; scalar_t__ window_cache; } ;
typedef  TYPE_1__ rep_state_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  void* apr_off_t ;
typedef  int /*<<< orphan*/  apr_file_t ;
struct TYPE_12__ {int /*<<< orphan*/  fs; int /*<<< orphan*/ * rfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/  SVN_FS_X__ITEM_TYPE_ANY_REP ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  auto_open_shared_file (TYPE_9__*) ; 
 int /*<<< orphan*/  auto_read_diff_version (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  auto_set_start_offset (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  block_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg__log_access (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_cached_window (int /*<<< orphan*/ **,TYPE_1__*,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_cached_window (int /*<<< orphan*/ *,TYPE_1__*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_fs_x__is_revision (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__rev_file_get (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__rev_file_offset (void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__rev_file_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  svn_fs_x__rev_file_stream (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_get_offset (void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_txdelta_read_svndiff_window (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_txdelta_skip_svndiff_window (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_delta_window(svn_txdelta_window_t **nwin, int this_chunk,
                  rep_state_t *rs, apr_pool_t *result_pool,
                  apr_pool_t *scratch_pool)
{
  svn_boolean_t is_cached;
  apr_off_t start_offset;
  apr_off_t end_offset;
  apr_pool_t *iterpool;
  svn_stream_t *stream;
  svn_fs_x__revision_file_t *file;
  svn_boolean_t cacheable = rs->chunk_index == 0
                         && svn_fs_x__is_revision(rs->rep_id.change_set)
                         && rs->window_cache;

  SVN_ERR_ASSERT(rs->chunk_index <= this_chunk);

  SVN_ERR(dbg__log_access(rs->sfile->fs, &rs->rep_id, NULL,
                          SVN_FS_X__ITEM_TYPE_ANY_REP, scratch_pool));

  /* Read the next window.  But first, try to find it in the cache. */
  if (cacheable)
    {
      SVN_ERR(get_cached_window(nwin, rs, this_chunk, &is_cached,
                                result_pool, scratch_pool));
      if (is_cached)
        return SVN_NO_ERROR;
    }

  /* someone has to actually read the data from file.  Open it */
  SVN_ERR(auto_open_shared_file(rs->sfile));
  file = rs->sfile->rfile;

  /* invoke the 'block-read' feature for non-txn data.
     However, don't do that if we are in the middle of some representation,
     because the block is unlikely to contain other data. */
  if (cacheable)
    {
      SVN_ERR(block_read(NULL, rs->sfile->fs, &rs->rep_id, file, NULL,
                         result_pool, scratch_pool));

      /* reading the whole block probably also provided us with the
         desired txdelta window */
      SVN_ERR(get_cached_window(nwin, rs, this_chunk, &is_cached,
                                result_pool, scratch_pool));
      if (is_cached)
        return SVN_NO_ERROR;
    }

  /* data is still not cached -> we need to read it.
     Make sure we have all the necessary info. */
  SVN_ERR(auto_set_start_offset(rs, scratch_pool));
  SVN_ERR(auto_read_diff_version(rs, scratch_pool));

  /* RS->FILE may be shared between RS instances -> make sure we point
   * to the right data. */
  start_offset = rs->start + rs->current;
  SVN_ERR(svn_fs_x__rev_file_seek(file, NULL, start_offset));

  /* Skip windows to reach the current chunk if we aren't there yet. */
  iterpool = svn_pool_create(scratch_pool);
  while (rs->chunk_index < this_chunk)
    {
      apr_file_t *apr_file;
      svn_pool_clear(iterpool);

      SVN_ERR(svn_fs_x__rev_file_get(&apr_file, file));
      SVN_ERR(svn_txdelta_skip_svndiff_window(apr_file, rs->ver, iterpool));
      rs->chunk_index++;
      SVN_ERR(svn_io_file_get_offset(&start_offset, apr_file, iterpool));

      rs->current = start_offset - rs->start;
      if (rs->current >= rs->size)
        return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                                _("Reading one svndiff window read "
                                  "beyond the end of the "
                                  "representation"));
    }
  svn_pool_destroy(iterpool);

  /* Actually read the next window. */
  SVN_ERR(svn_fs_x__rev_file_stream(&stream, file));
  SVN_ERR(svn_txdelta_read_svndiff_window(nwin, stream, rs->ver,
                                          result_pool));
  SVN_ERR(svn_fs_x__rev_file_offset(&end_offset, file));
  rs->current = end_offset - rs->start;
  if (rs->current > rs->size)
    return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                            _("Reading one svndiff window read beyond "
                              "the end of the representation"));

  /* the window has not been cached before, thus cache it now
   * (if caching is used for them at all) */
  if (cacheable)
    SVN_ERR(set_cached_window(*nwin, rs, start_offset, scratch_pool));

  return SVN_NO_ERROR;
}