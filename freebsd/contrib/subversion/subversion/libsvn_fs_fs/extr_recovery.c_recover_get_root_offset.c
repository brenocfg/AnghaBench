#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_3__ {int /*<<< orphan*/  file; int /*<<< orphan*/  is_packed; } ;
typedef  TYPE_1__ svn_fs_fs__revision_file_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_END ; 
 int /*<<< orphan*/  APR_SET ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_fs__parse_revision_trailer (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_read_full2 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stringbuf_ncreate (char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
recover_get_root_offset(apr_off_t *root_offset,
                        svn_revnum_t rev,
                        svn_fs_fs__revision_file_t *rev_file,
                        apr_pool_t *pool)
{
  char buffer[64];
  svn_stringbuf_t *trailer;
  apr_off_t start;
  apr_off_t end;
  apr_size_t len;

  SVN_ERR_ASSERT(!rev_file->is_packed);

  /* We will assume that the last line containing the two offsets (to the root
     node-id and to the changed path information) will never be longer than 64
     characters. */
  end = 0;
  SVN_ERR(svn_io_file_seek(rev_file->file, APR_END, &end, pool));

  if (end < sizeof(buffer))
    {
      len = (apr_size_t)end;
      start = 0;
    }
  else
    {
      len = sizeof(buffer);
      start = end - sizeof(buffer);
    }

  SVN_ERR(svn_io_file_seek(rev_file->file, APR_SET, &start, pool));
  SVN_ERR(svn_io_file_read_full2(rev_file->file, buffer, len,
                                 NULL, NULL, pool));

  trailer = svn_stringbuf_ncreate(buffer, len, pool);
  SVN_ERR(svn_fs_fs__parse_revision_trailer(root_offset, NULL, trailer, rev));

  return SVN_NO_ERROR;
}