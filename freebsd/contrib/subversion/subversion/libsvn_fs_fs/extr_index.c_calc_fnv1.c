#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ svn_fs_fs__revision_file_t ;
struct TYPE_8__ {int size; scalar_t__ type; int /*<<< orphan*/  fnv1_checksum; int /*<<< orphan*/  offset; } ;
typedef  TYPE_2__ svn_fs_fs__p2l_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_9__ {scalar_t__ digest; } ;
typedef  TYPE_3__ svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_checksum_ctx_t ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  apr_uint32_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SET ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_FS_FS__ITEM_TYPE_UNUSED ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * svn_checksum_ctx_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_final (TYPE_3__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_fnv1a_32x4 ; 
 int /*<<< orphan*/  svn_checksum_update (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  svn_io_file_read_full2 (int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
calc_fnv1(svn_fs_fs__p2l_entry_t *entry,
          svn_fs_fs__revision_file_t *rev_file,
          apr_pool_t *scratch_pool)
{
  unsigned char buffer[4096];
  svn_checksum_t *checksum;
  svn_checksum_ctx_t *context
    = svn_checksum_ctx_create(svn_checksum_fnv1a_32x4, scratch_pool);
  apr_off_t size = entry->size;

  /* Special rules apply to unused sections / items.  The data must be a
   * sequence of NUL bytes (not checked here) and the checksum is fixed to 0.
   */
  if (entry->type == SVN_FS_FS__ITEM_TYPE_UNUSED)
    {
      entry->fnv1_checksum = 0;
      return SVN_NO_ERROR;
    }

  /* Read the block and feed it to the checksum calculator. */
  SVN_ERR(svn_io_file_seek(rev_file->file, APR_SET, &entry->offset,
                           scratch_pool));
  while (size > 0)
    {
      apr_size_t to_read = size > sizeof(buffer)
                         ? sizeof(buffer)
                         : (apr_size_t)size;
      SVN_ERR(svn_io_file_read_full2(rev_file->file, buffer, to_read, NULL,
                                     NULL, scratch_pool));
      SVN_ERR(svn_checksum_update(context, buffer, to_read));
      size -= to_read;
    }

  /* Store final checksum in ENTRY. */
  SVN_ERR(svn_checksum_final(&checksum, context, scratch_pool));
  entry->fnv1_checksum = ntohl(*(const apr_uint32_t *)checksum->digest);

  return SVN_NO_ERROR;
}