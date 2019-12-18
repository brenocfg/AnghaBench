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
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  int svn_revnum_t ;
struct TYPE_8__ {TYPE_3__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
struct TYPE_9__ {int /*<<< orphan*/  file; scalar_t__ is_packed; } ;
typedef  TYPE_2__ svn_fs_fs__revision_file_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_10__ {int max_files_per_dir; } ;
typedef  TYPE_3__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_seek_where_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_END ; 
 int /*<<< orphan*/  APR_SET ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  aligned_seek (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__get_packed_offset (int*,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__parse_revision_trailer (int*,int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_io_file_read_full2 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stringbuf_ncreate (char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_root_changes_offset(apr_off_t *root_offset,
                        apr_off_t *changes_offset,
                        svn_fs_fs__revision_file_t *rev_file,
                        svn_fs_t *fs,
                        svn_revnum_t rev,
                        apr_pool_t *pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;
  apr_off_t rev_offset;
  apr_seek_where_t seek_relative;
  svn_stringbuf_t *trailer;
  char buffer[64];
  apr_off_t start;
  apr_off_t end;
  apr_size_t len;

  /* Determine where to seek to in the file.

     If we've got a pack file, we want to seek to the end of the desired
     revision.  But we don't track that, so we seek to the beginning of the
     next revision.

     Unless the next revision is in a different file, in which case, we can
     just seek to the end of the pack file -- just like we do in the
     non-packed case. */
  if (rev_file->is_packed && ((rev + 1) % ffd->max_files_per_dir != 0))
    {
      SVN_ERR(svn_fs_fs__get_packed_offset(&end, fs, rev + 1, pool));
      seek_relative = APR_SET;
    }
  else
    {
      seek_relative = APR_END;
      end = 0;
    }

  /* Offset of the revision from the start of the pack file, if applicable. */
  if (rev_file->is_packed)
    SVN_ERR(svn_fs_fs__get_packed_offset(&rev_offset, fs, rev, pool));
  else
    rev_offset = 0;

  /* We will assume that the last line containing the two offsets
     will never be longer than 64 characters. */
  SVN_ERR(svn_io_file_seek(rev_file->file, seek_relative, &end, pool));

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

  /* Read in this last block, from which we will identify the last line. */
  SVN_ERR(aligned_seek(fs, rev_file->file, NULL, start, pool));
  SVN_ERR(svn_io_file_read_full2(rev_file->file, buffer, len, NULL, NULL,
                                 pool));

  /* Parse the last line. */
  trailer = svn_stringbuf_ncreate(buffer, len, pool);
  SVN_ERR(svn_fs_fs__parse_revision_trailer(root_offset,
                                            changes_offset,
                                            trailer,
                                            rev));

  /* return absolute offsets */
  if (root_offset)
    *root_offset += rev_offset;
  if (changes_offset)
    *changes_offset += rev_offset;

  return SVN_NO_ERROR;
}