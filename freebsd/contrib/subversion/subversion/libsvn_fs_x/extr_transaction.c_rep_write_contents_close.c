#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  number; int /*<<< orphan*/  change_set; } ;
struct TYPE_17__ {TYPE_2__ id; int /*<<< orphan*/  expanded_size; void* size; } ;
typedef  TYPE_3__ svn_fs_x__representation_t ;
struct TYPE_18__ {void* offset; int item_count; int /*<<< orphan*/  fnv1_checksum; TYPE_5__* items; int /*<<< orphan*/  type; void* size; } ;
typedef  TYPE_4__ svn_fs_x__p2l_entry_t ;
struct TYPE_19__ {int /*<<< orphan*/  number; int /*<<< orphan*/  change_set; } ;
typedef  TYPE_5__ svn_fs_x__id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_20__ {void* delta_start; void* rep_offset; int /*<<< orphan*/  local_pool; int /*<<< orphan*/  lockcookie; int /*<<< orphan*/  fs; TYPE_7__* noderev; int /*<<< orphan*/  file; int /*<<< orphan*/  fnv1a_checksum; int /*<<< orphan*/  rep_stream; int /*<<< orphan*/  result_pool; int /*<<< orphan*/  sha1_checksum_ctx; int /*<<< orphan*/  md5_checksum_ctx; int /*<<< orphan*/  rep_size; int /*<<< orphan*/  delta_stream; } ;
typedef  TYPE_6__ rep_write_baton_t ;
typedef  void* apr_off_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;
struct TYPE_15__ {int /*<<< orphan*/  change_set; } ;
struct TYPE_21__ {TYPE_3__* data_rep; TYPE_1__ noderev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_FS_X__INVALID_CHANGE_SET ; 
 int /*<<< orphan*/  SVN_FS_X__ITEM_TYPE_FILE_REP ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  allocate_item_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* apr_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  apr_pool_cleanup_kill (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  digests_final (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_shared_rep (TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rep_write_cleanup ; 
 int /*<<< orphan*/  store_l2p_index_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_p2l_index_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_sha1_rep_mapping (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__change_set_by_txn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__get_txn_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__put_node_revision (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_get_offset (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_trunc (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_puts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unlock_proto_rev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
rep_write_contents_close(void *baton)
{
  rep_write_baton_t *b = baton;
  svn_fs_x__representation_t *rep;
  svn_fs_x__representation_t *old_rep;
  apr_off_t offset;
  apr_int64_t txn_id;

  rep = apr_pcalloc(b->result_pool, sizeof(*rep));

  /* Close our delta stream so the last bits of svndiff are written
     out. */
  SVN_ERR(svn_stream_close(b->delta_stream));

  /* Determine the length of the svndiff data. */
  SVN_ERR(svn_io_file_get_offset(&offset, b->file, b->local_pool));
  rep->size = offset - b->delta_start;

  /* Fill in the rest of the representation field. */
  rep->expanded_size = b->rep_size;
  txn_id = svn_fs_x__get_txn_id(b->noderev->noderev_id.change_set);
  rep->id.change_set = svn_fs_x__change_set_by_txn(txn_id);

  /* Finalize the checksum. */
  SVN_ERR(digests_final(rep, b->md5_checksum_ctx, b->sha1_checksum_ctx,
                        b->result_pool));

  /* Check and see if we already have a representation somewhere that's
     identical to the one we just wrote out. */
  SVN_ERR(get_shared_rep(&old_rep, b->fs, txn_id, rep, b->file, b->rep_offset,
                         NULL, b->result_pool, b->local_pool));

  if (old_rep)
    {
      /* We need to erase from the protorev the data we just wrote. */
      SVN_ERR(svn_io_file_trunc(b->file, b->rep_offset, b->local_pool));

      /* Use the old rep for this content. */
      b->noderev->data_rep = old_rep;
    }
  else
    {
      /* Write out our cosmetic end marker. */
      SVN_ERR(svn_stream_puts(b->rep_stream, "ENDREP\n"));
      SVN_ERR(allocate_item_index(&rep->id.number, b->fs, txn_id,
                                  b->local_pool));
      SVN_ERR(store_l2p_index_entry(b->fs, txn_id, b->rep_offset,
                                    rep->id.number, b->local_pool));

      b->noderev->data_rep = rep;
    }

  SVN_ERR(svn_stream_close(b->rep_stream));

  /* Remove cleanup callback. */
  apr_pool_cleanup_kill(b->local_pool, b, rep_write_cleanup);

  /* Write out the new node-rev information. */
  SVN_ERR(svn_fs_x__put_node_revision(b->fs, b->noderev, b->local_pool));
  if (!old_rep)
    {
      svn_fs_x__p2l_entry_t entry;
      svn_fs_x__id_t noderev_id;
      noderev_id.change_set = SVN_FS_X__INVALID_CHANGE_SET;
      noderev_id.number = rep->id.number;

      entry.offset = b->rep_offset;
      SVN_ERR(svn_io_file_get_offset(&offset, b->file, b->local_pool));
      entry.size = offset - b->rep_offset;
      entry.type = SVN_FS_X__ITEM_TYPE_FILE_REP;
      entry.item_count = 1;
      entry.items = &noderev_id;
      entry.fnv1_checksum = b->fnv1a_checksum;

      SVN_ERR(store_p2l_index_entry(b->fs, txn_id, &entry, b->local_pool));
    }

  SVN_ERR(svn_io_file_close(b->file, b->local_pool));

  /* Write the sha1->rep mapping *after* we successfully written node
   * revision to disk. */
  if (!old_rep)
    SVN_ERR(store_sha1_rep_mapping(b->fs, b->noderev, b->local_pool));

  SVN_ERR(unlock_proto_rev(b->fs, txn_id, b->lockcookie, b->local_pool));
  svn_pool_destroy(b->local_pool);

  return SVN_NO_ERROR;
}