#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int start; int end; int /*<<< orphan*/ * checksum; } ;
struct TYPE_11__ {int start; int end; int /*<<< orphan*/ * checksum; } ;
struct TYPE_10__ {int /*<<< orphan*/  start_revision; int /*<<< orphan*/  is_packed; } ;
struct TYPE_13__ {int /*<<< orphan*/ * owner; int /*<<< orphan*/ * pool; TYPE_3__ p2l_info; TYPE_2__ l2p_info; int /*<<< orphan*/  block_size; int /*<<< orphan*/ * l2p_stream; int /*<<< orphan*/ * p2l_stream; int /*<<< orphan*/ * stream; int /*<<< orphan*/ * file; TYPE_1__ file_info; TYPE_6__* fs; } ;
typedef  TYPE_4__ svn_fs_x__revision_file_t ;
struct TYPE_14__ {int /*<<< orphan*/  block_size; } ;
typedef  TYPE_5__ svn_fs_x__data_t ;
struct TYPE_15__ {TYPE_5__* fsap_data; } ;
typedef  TYPE_6__ svn_fs_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 TYPE_4__* apr_palloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static svn_fs_x__revision_file_t *
create_revision_file(svn_fs_t *fs,
                     apr_pool_t *result_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;

  svn_fs_x__revision_file_t *file = apr_palloc(result_pool, sizeof(*file));
  file->fs = fs;
  file->file_info.is_packed = FALSE;
  file->file_info.start_revision = SVN_INVALID_REVNUM;
  file->file = NULL;
  file->stream = NULL;
  file->p2l_stream = NULL;
  file->l2p_stream = NULL;
  file->block_size = ffd->block_size;
  file->l2p_info.start = -1;
  file->l2p_info.end = -1;
  file->l2p_info.checksum = NULL;
  file->p2l_info.start = -1;
  file->p2l_info.end = -1;
  file->p2l_info.checksum = NULL;
  file->pool = NULL;
  file->owner = result_pool;

  return file;
}