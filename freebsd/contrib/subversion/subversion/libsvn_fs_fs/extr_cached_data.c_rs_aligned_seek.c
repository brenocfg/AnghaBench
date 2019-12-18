#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_10__ {TYPE_3__* sfile; } ;
typedef  TYPE_4__ rep_state_t ;
struct TYPE_11__ {int /*<<< orphan*/  block_size; } ;
typedef  TYPE_5__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;
struct TYPE_9__ {TYPE_2__* rfile; TYPE_1__* fs; } ;
struct TYPE_8__ {int /*<<< orphan*/  file; } ;
struct TYPE_7__ {TYPE_5__* fsap_data; } ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_aligned_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
rs_aligned_seek(rep_state_t *rs,
                apr_off_t *buffer_start,
                apr_off_t offset,
                apr_pool_t *pool)
{
  fs_fs_data_t *ffd = rs->sfile->fs->fsap_data;
  return svn_error_trace(svn_io_file_aligned_seek(rs->sfile->rfile->file,
                                                  ffd->block_size,
                                                  buffer_start, offset,
                                                  pool));
}