#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_txdelta_window_handler_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_16__ {int /*<<< orphan*/  type; void* base_length; int /*<<< orphan*/  base_item_index; int /*<<< orphan*/  base_revision; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ svn_fs_fs__rep_header_t ;
struct TYPE_15__ {int /*<<< orphan*/  number; int /*<<< orphan*/  revision; } ;
struct TYPE_17__ {void* offset; int /*<<< orphan*/  fnv1_checksum; TYPE_1__ item; scalar_t__ type; void* size; } ;
typedef  TYPE_3__ svn_fs_fs__p2l_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_ctx_t ;
typedef  int svn_boolean_t ;
struct write_container_baton {scalar_t__ size; void* sha1_ctx; void* md5_ctx; int /*<<< orphan*/  stream; } ;
struct TYPE_18__ {int /*<<< orphan*/  txn_id; int /*<<< orphan*/  item_index; scalar_t__ expanded_size; void* size; int /*<<< orphan*/  revision; } ;
typedef  TYPE_4__ representation_t ;
typedef  int /*<<< orphan*/  node_revision_t ;
typedef  int /*<<< orphan*/  (* collection_writer_t ) (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ;
typedef  scalar_t__ apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  void* apr_off_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_FS_FS__ITEM_TYPE_DIR_PROPS ; 
 scalar_t__ SVN_FS_FS__ITEM_TYPE_DIR_REP ; 
 scalar_t__ SVN_FS_FS__ITEM_TYPE_FILE_PROPS ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  allocate_item_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 struct write_container_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  choose_delta_base (TYPE_4__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  digests_final (TYPE_4__*,void*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnv1a_checksum_finalize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnv1a_wrap_stream (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_shared_rep (TYPE_4__**,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  store_p2l_index_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 void* svn_checksum_ctx_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/  svn_checksum_sha1 ; 
 int /*<<< orphan*/  svn_fs_fs__get_contents (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__rep_delta ; 
 int /*<<< orphan*/  svn_fs_fs__rep_self_delta ; 
 scalar_t__ svn_fs_fs__use_log_addressing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__write_rep_header (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_get_offset (void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_trunc (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_stream_create (struct write_container_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_from_aprfile2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_puts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_txdelta_target_push (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txdelta_to_svndiff (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_container_handler ; 

__attribute__((used)) static svn_error_t *
write_container_delta_rep(representation_t *rep,
                          apr_file_t *file,
                          void *collection,
                          collection_writer_t writer,
                          svn_fs_t *fs,
                          node_revision_t *noderev,
                          apr_hash_t *reps_hash,
                          svn_boolean_t allow_rep_sharing,
                          apr_uint32_t item_type,
                          apr_pool_t *scratch_pool)
{
  svn_txdelta_window_handler_t diff_wh;
  void *diff_whb;

  svn_stream_t *file_stream;
  svn_stream_t *stream;
  representation_t *base_rep;
  svn_checksum_ctx_t *fnv1a_checksum_ctx;
  svn_stream_t *source;
  svn_fs_fs__rep_header_t header = { 0 };

  apr_off_t rep_end = 0;
  apr_off_t delta_start = 0;
  apr_off_t offset = 0;

  struct write_container_baton *whb;
  svn_boolean_t is_props = (item_type == SVN_FS_FS__ITEM_TYPE_FILE_PROPS)
                        || (item_type == SVN_FS_FS__ITEM_TYPE_DIR_PROPS);

  /* Get the base for this delta. */
  SVN_ERR(choose_delta_base(&base_rep, fs, noderev, is_props, scratch_pool));
  SVN_ERR(svn_fs_fs__get_contents(&source, fs, base_rep, FALSE, scratch_pool));

  SVN_ERR(svn_io_file_get_offset(&offset, file, scratch_pool));

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

  file_stream = svn_stream_from_aprfile2(file, TRUE, scratch_pool);
  if (svn_fs_fs__use_log_addressing(fs))
    file_stream = fnv1a_wrap_stream(&fnv1a_checksum_ctx, file_stream,
                                    scratch_pool);
  else
    fnv1a_checksum_ctx = NULL;
  SVN_ERR(svn_fs_fs__write_rep_header(&header, file_stream, scratch_pool));
  SVN_ERR(svn_io_file_get_offset(&delta_start, file, scratch_pool));

  /* Prepare to write the svndiff data. */
  txdelta_to_svndiff(&diff_wh, &diff_whb, file_stream, fs, scratch_pool);

  whb = apr_pcalloc(scratch_pool, sizeof(*whb));
  whb->stream = svn_txdelta_target_push(diff_wh, diff_whb, source,
                                        scratch_pool);
  whb->size = 0;
  whb->md5_ctx = svn_checksum_ctx_create(svn_checksum_md5, scratch_pool);
  if (item_type != SVN_FS_FS__ITEM_TYPE_DIR_REP)
    whb->sha1_ctx = svn_checksum_ctx_create(svn_checksum_sha1, scratch_pool);

  /* serialize the hash */
  stream = svn_stream_create(whb, scratch_pool);
  svn_stream_set_write(stream, write_container_handler);

  SVN_ERR(writer(stream, collection, scratch_pool));
  SVN_ERR(svn_stream_close(whb->stream));

  /* Store the results. */
  SVN_ERR(digests_final(rep, whb->md5_ctx, whb->sha1_ctx, scratch_pool));

  /* Update size info. */
  SVN_ERR(svn_io_file_get_offset(&rep_end, file, scratch_pool));
  rep->size = rep_end - delta_start;
  rep->expanded_size = whb->size;

  /* Check and see if we already have a representation somewhere that's
     identical to the one we just wrote out. */
  if (allow_rep_sharing)
    {
      representation_t *old_rep;
      SVN_ERR(get_shared_rep(&old_rep, fs, rep, file, offset, reps_hash,
                             scratch_pool, scratch_pool));

      if (old_rep)
        {
          /* We need to erase from the protorev the data we just wrote. */
          SVN_ERR(svn_io_file_trunc(file, offset, scratch_pool));

          /* Use the old rep for this content. */
          memcpy(rep, old_rep, sizeof (*rep));
          return SVN_NO_ERROR;
        }
    }

  /* Write out our cosmetic end marker. */
  SVN_ERR(svn_stream_puts(file_stream, "ENDREP\n"));

  SVN_ERR(allocate_item_index(&rep->item_index, fs, &rep->txn_id,
                              offset, scratch_pool));

  if (svn_fs_fs__use_log_addressing(fs))
    {
      svn_fs_fs__p2l_entry_t entry;

      entry.offset = offset;
      SVN_ERR(svn_io_file_get_offset(&offset, file, scratch_pool));
      entry.size = offset - entry.offset;
      entry.type = item_type;
      entry.item.revision = SVN_INVALID_REVNUM;
      entry.item.number = rep->item_index;
      SVN_ERR(fnv1a_checksum_finalize(&entry.fnv1_checksum,
                                      fnv1a_checksum_ctx,
                                      scratch_pool));

      SVN_ERR(store_p2l_index_entry(fs, &rep->txn_id, &entry, scratch_pool));
    }

  return SVN_NO_ERROR;
}