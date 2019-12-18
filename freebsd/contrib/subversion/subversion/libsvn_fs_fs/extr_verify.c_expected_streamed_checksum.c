#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int size; } ;
typedef  TYPE_1__ svn_fs_fs__p2l_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {scalar_t__ digest; } ;
typedef  TYPE_2__ svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_checksum_ctx_t ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  apr_uint32_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int apr_off_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int STREAM_THRESHOLD ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  expected_checksum (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * svn_checksum_ctx_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_final (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_fnv1a_32x4 ; 
 int /*<<< orphan*/  svn_checksum_update (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  svn_io_file_read_full2 (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
expected_streamed_checksum(apr_file_t *file,
                           svn_fs_fs__p2l_entry_t *entry,
                           apr_pool_t *pool)
{
  unsigned char buffer[STREAM_THRESHOLD];
  svn_checksum_t *checksum;
  svn_checksum_ctx_t *context
    = svn_checksum_ctx_create(svn_checksum_fnv1a_32x4, pool);
  apr_off_t size = entry->size;

  while (size > 0)
    {
      apr_size_t to_read = size > sizeof(buffer)
                         ? sizeof(buffer)
                         : (apr_size_t)size;
      SVN_ERR(svn_io_file_read_full2(file, buffer, to_read, NULL, NULL,
                                     pool));
      SVN_ERR(svn_checksum_update(context, buffer, to_read));
      size -= to_read;
    }

  SVN_ERR(svn_checksum_final(&checksum, context, pool));
  SVN_ERR(expected_checksum(file, entry,
                            ntohl(*(const apr_uint32_t *)checksum->digest),
                            pool));

  return SVN_NO_ERROR;
}