#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_8__ {TYPE_3__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
struct TYPE_9__ {int l2p_offset; int p2l_offset; int footer_offset; int /*<<< orphan*/ * pool; int /*<<< orphan*/ * p2l_checksum; int /*<<< orphan*/ * l2p_checksum; int /*<<< orphan*/  block_size; int /*<<< orphan*/ * l2p_stream; int /*<<< orphan*/ * p2l_stream; int /*<<< orphan*/ * stream; int /*<<< orphan*/ * file; int /*<<< orphan*/  start_revision; int /*<<< orphan*/  is_packed; } ;
typedef  TYPE_2__ svn_fs_fs__revision_file_t ;
struct TYPE_10__ {int /*<<< orphan*/  block_size; } ;
typedef  TYPE_3__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_fs_fs__is_packed_rev (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__packed_base_rev (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
init_revision_file(svn_fs_fs__revision_file_t *file,
                   svn_fs_t *fs,
                   svn_revnum_t revision,
                   apr_pool_t *pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;

  file->is_packed = svn_fs_fs__is_packed_rev(fs, revision);
  file->start_revision = svn_fs_fs__packed_base_rev(fs, revision);

  file->file = NULL;
  file->stream = NULL;
  file->p2l_stream = NULL;
  file->l2p_stream = NULL;
  file->block_size = ffd->block_size;
  file->l2p_offset = -1;
  file->l2p_checksum = NULL;
  file->p2l_offset = -1;
  file->p2l_checksum = NULL;
  file->footer_offset = -1;
  file->pool = pool;
}