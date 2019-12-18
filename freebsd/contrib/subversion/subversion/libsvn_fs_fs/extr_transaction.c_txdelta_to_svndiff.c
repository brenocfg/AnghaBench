#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_txdelta_window_handler_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_4__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
struct TYPE_5__ {scalar_t__ delta_compression_type; scalar_t__ format; int /*<<< orphan*/  delta_compression_level; } ;
typedef  TYPE_2__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int) ; 
 scalar_t__ SVN_FS_FS__MIN_SVNDIFF1_FORMAT ; 
 scalar_t__ SVN_FS_FS__MIN_SVNDIFF2_FORMAT ; 
 scalar_t__ compression_type_lz4 ; 
 scalar_t__ compression_type_zlib ; 
 int /*<<< orphan*/  svn_txdelta_to_svndiff3 (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
txdelta_to_svndiff(svn_txdelta_window_handler_t *handler,
                   void **handler_baton,
                   svn_stream_t *output,
                   svn_fs_t *fs,
                   apr_pool_t *pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;
  int svndiff_version;

  if (ffd->delta_compression_type == compression_type_lz4)
    {
      SVN_ERR_ASSERT_NO_RETURN(ffd->format >= SVN_FS_FS__MIN_SVNDIFF2_FORMAT);
      svndiff_version = 2;
    }
  else if (ffd->delta_compression_type == compression_type_zlib)
    {
      SVN_ERR_ASSERT_NO_RETURN(ffd->format >= SVN_FS_FS__MIN_SVNDIFF1_FORMAT);
      svndiff_version = 1;
    }
  else
    {
      svndiff_version = 0;
    }

  svn_txdelta_to_svndiff3(handler, handler_baton, output, svndiff_version,
                          ffd->delta_compression_level, pool);
}