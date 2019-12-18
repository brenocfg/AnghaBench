#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_txdelta_window_handler_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
struct TYPE_22__ {int /*<<< orphan*/  number; int /*<<< orphan*/  change_set; } ;
struct TYPE_23__ {int /*<<< orphan*/  size; TYPE_2__ id; } ;
typedef  TYPE_3__ svn_fs_x__representation_t ;
struct TYPE_24__ {int /*<<< orphan*/  type; int /*<<< orphan*/  base_length; int /*<<< orphan*/  base_item_index; int /*<<< orphan*/  base_revision; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ svn_fs_x__rep_header_t ;
struct TYPE_21__ {int /*<<< orphan*/  change_set; } ;
struct TYPE_25__ {TYPE_1__ noderev_id; } ;
typedef  TYPE_5__ svn_fs_x__noderev_t ;
struct TYPE_26__ {int /*<<< orphan*/  delta_compression_level; } ;
typedef  TYPE_6__ svn_fs_x__data_t ;
struct TYPE_27__ {TYPE_6__* fsap_data; } ;
typedef  TYPE_7__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_28__ {int /*<<< orphan*/ * result_pool; int /*<<< orphan*/  delta_stream; int /*<<< orphan*/  rep_stream; int /*<<< orphan*/  local_pool; int /*<<< orphan*/  delta_start; int /*<<< orphan*/  rep_offset; int /*<<< orphan*/  fnv1a_checksum; int /*<<< orphan*/ * file; int /*<<< orphan*/  lockcookie; TYPE_5__* noderev; scalar_t__ rep_size; TYPE_7__* fs; void* md5_checksum_ctx; void* sha1_checksum_ctx; } ;
typedef  TYPE_8__ rep_write_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_8__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  choose_delta_base (TYPE_3__**,TYPE_7__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_writable_proto_rev (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rep_write_cleanup ; 
 int /*<<< orphan*/  svn_checksum__wrap_write_stream_fnv1a_32x4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* svn_checksum_ctx_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/  svn_checksum_sha1 ; 
 int /*<<< orphan*/  svn_fs_x__get_contents (int /*<<< orphan*/ **,TYPE_7__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__get_revnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__get_txn_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__rep_delta ; 
 int /*<<< orphan*/  svn_fs_x__rep_self_delta ; 
 int /*<<< orphan*/  svn_fs_x__write_rep_header (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_get_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_disown (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_from_aprfile2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_txdelta_target_push (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_txdelta_to_svndiff3 (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
rep_write_get_baton(rep_write_baton_t **wb_p,
                    svn_fs_t *fs,
                    svn_fs_x__noderev_t *noderev,
                    apr_pool_t *result_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;
  rep_write_baton_t *b;
  apr_file_t *file;
  svn_fs_x__representation_t *base_rep;
  svn_stream_t *source;
  svn_txdelta_window_handler_t wh;
  void *whb;
  int diff_version = 1;
  svn_fs_x__rep_header_t header = { 0 };
  svn_fs_x__txn_id_t txn_id
    = svn_fs_x__get_txn_id(noderev->noderev_id.change_set);

  b = apr_pcalloc(result_pool, sizeof(*b));

  b->sha1_checksum_ctx = svn_checksum_ctx_create(svn_checksum_sha1,
                                                 result_pool);
  b->md5_checksum_ctx = svn_checksum_ctx_create(svn_checksum_md5,
                                                result_pool);

  b->fs = fs;
  b->result_pool = result_pool;
  b->local_pool = svn_pool_create(result_pool);
  b->rep_size = 0;
  b->noderev = noderev;

  /* Open the prototype rev file and seek to its end. */
  SVN_ERR(get_writable_proto_rev(&file, &b->lockcookie, fs, txn_id,
                                 b->local_pool));

  b->file = file;
  b->rep_stream = svn_checksum__wrap_write_stream_fnv1a_32x4(
                              &b->fnv1a_checksum,
                              svn_stream_from_aprfile2(file, TRUE,
                                                       b->local_pool),
                              b->local_pool);

  SVN_ERR(svn_io_file_get_offset(&b->rep_offset, file, b->local_pool));

  /* Get the base for this delta. */
  SVN_ERR(choose_delta_base(&base_rep, fs, noderev, FALSE, b->local_pool));
  SVN_ERR(svn_fs_x__get_contents(&source, fs, base_rep, TRUE,
                                 b->local_pool));

  /* Write out the rep header. */
  if (base_rep)
    {
      header.base_revision = svn_fs_x__get_revnum(base_rep->id.change_set);
      header.base_item_index = base_rep->id.number;
      header.base_length = base_rep->size;
      header.type = svn_fs_x__rep_delta;
    }
  else
    {
      header.type = svn_fs_x__rep_self_delta;
    }
  SVN_ERR(svn_fs_x__write_rep_header(&header, b->rep_stream,
                                     b->local_pool));

  /* Now determine the offset of the actual svndiff data. */
  SVN_ERR(svn_io_file_get_offset(&b->delta_start, file, b->local_pool));

  /* Cleanup in case something goes wrong. */
  apr_pool_cleanup_register(b->local_pool, b, rep_write_cleanup,
                            apr_pool_cleanup_null);

  /* Prepare to write the svndiff data. */
  svn_txdelta_to_svndiff3(&wh,
                          &whb,
                          svn_stream_disown(b->rep_stream, b->result_pool),
                          diff_version,
                          ffd->delta_compression_level,
                          result_pool);

  b->delta_stream = svn_txdelta_target_push(wh, whb, source,
                                            b->result_pool);

  *wb_p = b;

  return SVN_NO_ERROR;
}