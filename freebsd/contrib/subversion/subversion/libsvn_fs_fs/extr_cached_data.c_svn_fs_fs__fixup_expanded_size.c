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
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_12__ {int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ svn_fs_fs__revision_file_t ;
struct TYPE_13__ {scalar_t__ type; } ;
typedef  TYPE_2__ svn_fs_fs__rep_header_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_14__ {void* kind; int /*<<< orphan*/  digest; } ;
typedef  TYPE_3__ svn_checksum_t ;
struct TYPE_15__ {int expanded_size; int size; int /*<<< orphan*/  item_index; int /*<<< orphan*/  revision; int /*<<< orphan*/  sha1_digest; scalar_t__ has_sha1; int /*<<< orphan*/  md5_digest; int /*<<< orphan*/  txn_id; } ;
typedef  TYPE_4__ representation_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  open_and_seek_revision (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_checksum_empty_checksum (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_match (TYPE_3__*,TYPE_3__*) ; 
 void* svn_checksum_md5 ; 
 void* svn_checksum_sha1 ; 
 int /*<<< orphan*/  svn_fs_fs__close_revision_file (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_fs_fs__id_txn_used (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__read_rep_header (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_fs__rep_plain ; 

svn_error_t *
svn_fs_fs__fixup_expanded_size(svn_fs_t *fs,
                               representation_t *rep,
                               apr_pool_t *scratch_pool)
{
  svn_checksum_t checksum;
  svn_checksum_t *empty_md5;
  svn_fs_fs__revision_file_t *revision_file;
  svn_fs_fs__rep_header_t *rep_header;

  /* Anything to do at all?
   *
   * Note that a 0 SIZE is only possible for PLAIN reps due to the SVN\1
   * magic prefix in any DELTA rep. */
  if (!rep || rep->expanded_size != 0 || rep->size == 0)
    return SVN_NO_ERROR;

  /* This function may only be called for committed data. */
  assert(!svn_fs_fs__id_txn_used(&rep->txn_id));

  /* EXPANDED_SIZE is 0. If the MD5 does not match the one for empty
   * contents, we know that EXPANDED_SIZE == 0 is wrong and needs to
   * be set to the actual value given by SIZE.
   *
   * Using svn_checksum_match() will also accept all-zero values for
   * the MD5 digest and only report a mismatch if the MD5 has actually
   * been given. */
  empty_md5 = svn_checksum_empty_checksum(svn_checksum_md5, scratch_pool);

  checksum.digest = rep->md5_digest;
  checksum.kind = svn_checksum_md5;
  if (!svn_checksum_match(empty_md5, &checksum))
    {
      rep->expanded_size = rep->size;
      return SVN_NO_ERROR;
    }

  /* Data in the rep-cache.db does not have MD5 checksums (all zero) on it.
   * Compare SHA1 instead. */
  if (rep->has_sha1)
    {
      svn_checksum_t *empty_sha1
        = svn_checksum_empty_checksum(svn_checksum_sha1, scratch_pool);

      checksum.digest = rep->sha1_digest;
      checksum.kind = svn_checksum_sha1;
      if (!svn_checksum_match(empty_sha1, &checksum))
        {
          rep->expanded_size = rep->size;
          return SVN_NO_ERROR;
        }
    }

  /* Only two cases are left here.
   * (1) A non-empty PLAIN rep with a MD5 collision on EMPTY_MD5.
   * (2) A DELTA rep with zero-length output. */

  /* SVN always stores a DELTA rep with zero-length output as an empty
   * sequence of txdelta windows, i.e. as "SVN\1".  In that case, SIZE is
   * 4 bytes.  There is no other possible DELTA rep of that size and any
   * PLAIN rep of 4 bytes would produce a different MD5.  Hence, if SIZE is
   * actually 4 here, we know that this is an empty DELTA rep.
   *
   * Note that it is technically legal to have DELTA reps with a 0 length
   * output window.  Their on-disk size would be longer.  We handle that
   * case later together with the equally unlikely MD5 collision. */
  if (rep->size == 4)
    {
      /* EXPANDED_SIZE is already 0. */
      return SVN_NO_ERROR;
    }

  /* We still have the two options, PLAIN or DELTA rep.  At this point, we
   * are in an extremely unlikely case and can spend some time to figure it
   * out.  So, let's just look at the representation header. */
  SVN_ERR(open_and_seek_revision(&revision_file, fs, rep->revision,
                                 rep->item_index, scratch_pool));
  SVN_ERR(svn_fs_fs__read_rep_header(&rep_header, revision_file->stream,
                                     scratch_pool, scratch_pool));
  SVN_ERR(svn_fs_fs__close_revision_file(revision_file));

  /* Only for PLAIN reps do we have to correct EXPANDED_SIZE. */
  if (rep_header->type == svn_fs_fs__rep_plain)
    rep->expanded_size = rep->size;

  return SVN_NO_ERROR;
}