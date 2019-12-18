#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  number; void* revision; } ;
struct TYPE_13__ {void* offset; int /*<<< orphan*/  fnv1_checksum; TYPE_1__ item; int /*<<< orphan*/  type; void* size; } ;
typedef  TYPE_2__ svn_fs_fs__p2l_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct rep_write_baton {void* delta_start; void* rep_offset; int /*<<< orphan*/  scratch_pool; int /*<<< orphan*/  lockcookie; int /*<<< orphan*/  fs; TYPE_4__* noderev; int /*<<< orphan*/  file; int /*<<< orphan*/  fnv1a_checksum_ctx; int /*<<< orphan*/  rep_stream; int /*<<< orphan*/  result_pool; int /*<<< orphan*/  sha1_checksum_ctx; int /*<<< orphan*/  md5_checksum_ctx; int /*<<< orphan*/  rep_size; scalar_t__ delta_stream; } ;
struct TYPE_14__ {int /*<<< orphan*/  txn_id; int /*<<< orphan*/  item_index; void* revision; int /*<<< orphan*/  expanded_size; void* size; } ;
typedef  TYPE_3__ representation_t ;
typedef  void* apr_off_t ;
struct TYPE_15__ {int /*<<< orphan*/  id; TYPE_3__* data_rep; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_FS_FS__ITEM_TYPE_FILE_REP ; 
 void* SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  allocate_item_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 TYPE_3__* apr_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  apr_pool_cleanup_kill (int /*<<< orphan*/ ,struct rep_write_baton*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  digests_final (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnv1a_checksum_finalize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_shared_rep (TYPE_3__**,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rep_write_cleanup ; 
 int /*<<< orphan*/  set_uniquifier (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_p2l_index_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_sha1_rep_mapping (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_fs__id_txn_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__put_node_revision (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_fs_fs__use_log_addressing (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_get_offset (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_trunc (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_close (scalar_t__) ; 
 int /*<<< orphan*/  svn_stream_puts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unlock_proto_rev (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
rep_write_contents_close(void *baton)
{
  struct rep_write_baton *b = baton;
  representation_t *rep;
  representation_t *old_rep;
  apr_off_t offset;

  rep = apr_pcalloc(b->result_pool, sizeof(*rep));

  /* Close our delta stream so the last bits of svndiff are written
     out. */
  if (b->delta_stream)
    SVN_ERR(svn_stream_close(b->delta_stream));

  /* Determine the length of the svndiff data. */
  SVN_ERR(svn_io_file_get_offset(&offset, b->file, b->scratch_pool));
  rep->size = offset - b->delta_start;

  /* Fill in the rest of the representation field. */
  rep->expanded_size = b->rep_size;
  rep->txn_id = *svn_fs_fs__id_txn_id(b->noderev->id);
  SVN_ERR(set_uniquifier(b->fs, rep, b->scratch_pool));
  rep->revision = SVN_INVALID_REVNUM;

  /* Finalize the checksum. */
  SVN_ERR(digests_final(rep, b->md5_checksum_ctx, b->sha1_checksum_ctx,
                        b->result_pool));

  /* Check and see if we already have a representation somewhere that's
     identical to the one we just wrote out. */
  SVN_ERR(get_shared_rep(&old_rep, b->fs, rep, b->file, b->rep_offset, NULL,
                         b->result_pool, b->scratch_pool));

  if (old_rep)
    {
      /* We need to erase from the protorev the data we just wrote. */
      SVN_ERR(svn_io_file_trunc(b->file, b->rep_offset, b->scratch_pool));

      /* Use the old rep for this content. */
      b->noderev->data_rep = old_rep;
    }
  else
    {
      /* Write out our cosmetic end marker. */
      SVN_ERR(svn_stream_puts(b->rep_stream, "ENDREP\n"));
      SVN_ERR(allocate_item_index(&rep->item_index, b->fs, &rep->txn_id,
                                  b->rep_offset, b->scratch_pool));

      b->noderev->data_rep = rep;
    }

  /* Remove cleanup callback. */
  apr_pool_cleanup_kill(b->scratch_pool, b, rep_write_cleanup);

  /* Write out the new node-rev information. */
  SVN_ERR(svn_fs_fs__put_node_revision(b->fs, b->noderev->id, b->noderev,
                                       FALSE, b->scratch_pool));
  if (!old_rep && svn_fs_fs__use_log_addressing(b->fs))
    {
      svn_fs_fs__p2l_entry_t entry;

      entry.offset = b->rep_offset;
      SVN_ERR(svn_io_file_get_offset(&offset, b->file, b->scratch_pool));
      entry.size = offset - b->rep_offset;
      entry.type = SVN_FS_FS__ITEM_TYPE_FILE_REP;
      entry.item.revision = SVN_INVALID_REVNUM;
      entry.item.number = rep->item_index;
      SVN_ERR(fnv1a_checksum_finalize(&entry.fnv1_checksum,
                                      b->fnv1a_checksum_ctx,
                                      b->scratch_pool));

      SVN_ERR(store_p2l_index_entry(b->fs, &rep->txn_id, &entry,
                                    b->scratch_pool));
    }

  SVN_ERR(svn_io_file_close(b->file, b->scratch_pool));

  /* Write the sha1->rep mapping *after* we successfully written node
   * revision to disk. */
  if (!old_rep)
    SVN_ERR(store_sha1_rep_mapping(b->fs, b->noderev, b->scratch_pool));

  SVN_ERR(unlock_proto_rev(b->fs, &rep->txn_id, b->lockcookie,
                           b->scratch_pool));
  svn_pool_destroy(b->scratch_pool);

  return SVN_NO_ERROR;
}