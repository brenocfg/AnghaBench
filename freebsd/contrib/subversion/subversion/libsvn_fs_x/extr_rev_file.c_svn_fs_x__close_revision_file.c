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
struct TYPE_4__ {int start; } ;
struct TYPE_5__ {TYPE_1__ l2p_info; int /*<<< orphan*/ * p2l_stream; int /*<<< orphan*/ * l2p_stream; int /*<<< orphan*/ * stream; int /*<<< orphan*/ * file; scalar_t__ pool; } ;
typedef  TYPE_2__ svn_fs_x__revision_file_t ;
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  svn_pool_clear (scalar_t__) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__close_revision_file(svn_fs_x__revision_file_t *file)
{
  /* Close sub-objects properly */
  if (file->stream)
    SVN_ERR(svn_stream_close(file->stream));
  if (file->file)
    SVN_ERR(svn_io_file_close(file->file, file->pool));

  /* Release the memory. */
  if (file->pool)
    svn_pool_clear(file->pool);

  /* Reset pointers to objects previously allocated from FILE->POOL. */
  file->file = NULL;
  file->stream = NULL;
  file->l2p_stream = NULL;
  file->p2l_stream = NULL;

  /* Cause any index data getters to re-read the footer. */
  file->l2p_info.start = -1;
  return SVN_NO_ERROR;
}