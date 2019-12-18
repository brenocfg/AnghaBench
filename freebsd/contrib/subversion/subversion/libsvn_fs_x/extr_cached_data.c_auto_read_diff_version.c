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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int ver; int current; scalar_t__ chunk_index; TYPE_1__* sfile; int /*<<< orphan*/  start; } ;
typedef  TYPE_2__ rep_state_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_4__ {int /*<<< orphan*/  rfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__rev_file_read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  svn_fs_x__rev_file_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t*
auto_read_diff_version(rep_state_t *rs,
                       apr_pool_t *scratch_pool)
{
  if (rs->ver == -1)
    {
      char buf[4];
      SVN_ERR(svn_fs_x__rev_file_seek(rs->sfile->rfile, NULL, rs->start));
      SVN_ERR(svn_fs_x__rev_file_read(rs->sfile->rfile, buf, sizeof(buf)));

      /* ### Layering violation */
      if (! ((buf[0] == 'S') && (buf[1] == 'V') && (buf[2] == 'N')))
        return svn_error_create
          (SVN_ERR_FS_CORRUPT, NULL,
           _("Malformed svndiff data in representation"));
      rs->ver = buf[3];

      rs->chunk_index = 0;
      rs->current = 4;
    }

  return SVN_NO_ERROR;
}