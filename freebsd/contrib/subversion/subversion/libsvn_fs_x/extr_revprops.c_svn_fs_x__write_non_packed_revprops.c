#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  digest; } ;
typedef  TYPE_1__ svn_checksum_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * svn_checksum__wrap_write_stream (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_fnv1a_32x4 ; 
 int /*<<< orphan*/  svn_checksum_size (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_fs_x__write_properties (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_write_full (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_from_aprfile2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__write_non_packed_revprops(apr_file_t *file,
                                    apr_hash_t *proplist,
                                    apr_pool_t *scratch_pool)
{
  svn_stream_t *stream;
  svn_checksum_t *checksum;

  stream = svn_stream_from_aprfile2(file, TRUE, scratch_pool);
  stream = svn_checksum__wrap_write_stream(&checksum, stream,
                                           svn_checksum_fnv1a_32x4,
                                           scratch_pool);
  SVN_ERR(svn_fs_x__write_properties(stream, proplist, scratch_pool));
  SVN_ERR(svn_stream_close(stream));

  /* Append the checksum */
  SVN_ERR(svn_io_file_write_full(file, checksum->digest,
                                 svn_checksum_size(checksum), NULL,
                                 scratch_pool));

  return SVN_NO_ERROR;
}