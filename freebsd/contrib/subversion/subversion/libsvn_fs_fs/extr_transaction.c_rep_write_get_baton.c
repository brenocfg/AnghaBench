#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_txdelta_window_handler_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_9__ {int /*<<< orphan*/  type; int /*<<< orphan*/  base_length; int /*<<< orphan*/  base_item_index; int /*<<< orphan*/  base_revision; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ svn_fs_fs__rep_header_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct rep_write_baton {int /*<<< orphan*/  scratch_pool; int /*<<< orphan*/  delta_stream; int /*<<< orphan*/  rep_stream; int /*<<< orphan*/  delta_start; int /*<<< orphan*/  rep_offset; int /*<<< orphan*/  fnv1a_checksum_ctx; int /*<<< orphan*/ * file; int /*<<< orphan*/  lockcookie; TYPE_3__* noderev; scalar_t__ rep_size; int /*<<< orphan*/ * result_pool; int /*<<< orphan*/ * fs; void* md5_checksum_ctx; void* sha1_checksum_ctx; } ;
struct TYPE_10__ {int /*<<< orphan*/  size; int /*<<< orphan*/  item_index; int /*<<< orphan*/  revision; } ;
typedef  TYPE_2__ representation_t ;
struct TYPE_11__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ node_revision_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 struct rep_write_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ ,struct rep_write_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  choose_delta_base (TYPE_2__**,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnv1a_wrap_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_writable_proto_rev (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rep_write_cleanup ; 
 void* svn_checksum_ctx_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/  svn_checksum_sha1 ; 
 int /*<<< orphan*/  svn_fs_fs__get_contents (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__id_txn_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__rep_delta ; 
 int /*<<< orphan*/  svn_fs_fs__rep_self_delta ; 
 scalar_t__ svn_fs_fs__use_log_addressing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__write_rep_header (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_get_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_from_aprfile2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_txdelta_target_push (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txdelta_to_svndiff (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
rep_write_get_baton(struct rep_write_baton **wb_p,
                    svn_fs_t *fs,
                    node_revision_t *noderev,
                    apr_pool_t *pool)
{
  struct rep_write_baton *b;
  apr_file_t *file;
  representation_t *base_rep;
  svn_stream_t *source;
  svn_txdelta_window_handler_t wh;
  void *whb;
  svn_fs_fs__rep_header_t header = { 0 };

  b = apr_pcalloc(pool, sizeof(*b));

  b->sha1_checksum_ctx = svn_checksum_ctx_create(svn_checksum_sha1, pool);
  b->md5_checksum_ctx = svn_checksum_ctx_create(svn_checksum_md5, pool);

  b->fs = fs;
  b->result_pool = pool;
  b->scratch_pool = svn_pool_create(pool);
  b->rep_size = 0;
  b->noderev = noderev;

  /* Open the prototype rev file and seek to its end. */
  SVN_ERR(get_writable_proto_rev(&file, &b->lockcookie,
                                 fs, svn_fs_fs__id_txn_id(noderev->id),
                                 b->scratch_pool));

  b->file = file;
  b->rep_stream = svn_stream_from_aprfile2(file, TRUE, b->scratch_pool);
  if (svn_fs_fs__use_log_addressing(fs))
    b->rep_stream = fnv1a_wrap_stream(&b->fnv1a_checksum_ctx, b->rep_stream,
                                      b->scratch_pool);

  SVN_ERR(svn_io_file_get_offset(&b->rep_offset, file, b->scratch_pool));

  /* Get the base for this delta. */
  SVN_ERR(choose_delta_base(&base_rep, fs, noderev, FALSE, b->scratch_pool));
  SVN_ERR(svn_fs_fs__get_contents(&source, fs, base_rep, TRUE,
                                  b->scratch_pool));

  /* Write out the rep header. */
  if (base_rep)
    {
      header.base_revision = base_rep->revision;
      header.base_item_index = base_rep->item_index;
      header.base_length = base_rep->size;
      header.type = svn_fs_fs__rep_delta;
    }
  else
    {
      header.type = svn_fs_fs__rep_self_delta;
    }
  SVN_ERR(svn_fs_fs__write_rep_header(&header, b->rep_stream,
                                      b->scratch_pool));

  /* Now determine the offset of the actual svndiff data. */
  SVN_ERR(svn_io_file_get_offset(&b->delta_start, file,
                                 b->scratch_pool));

  /* Cleanup in case something goes wrong. */
  apr_pool_cleanup_register(b->scratch_pool, b, rep_write_cleanup,
                            apr_pool_cleanup_null);

  /* Prepare to write the svndiff data. */
  txdelta_to_svndiff(&wh, &whb, b->rep_stream, fs, pool);

  b->delta_stream = svn_txdelta_target_push(wh, whb, source,
                                            b->scratch_pool);

  *wb_p = b;

  return SVN_NO_ERROR;
}