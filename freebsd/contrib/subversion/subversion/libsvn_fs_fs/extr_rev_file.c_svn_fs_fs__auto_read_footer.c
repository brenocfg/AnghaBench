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
struct TYPE_6__ {unsigned char* data; size_t len; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
struct TYPE_7__ {int l2p_offset; int footer_offset; int /*<<< orphan*/  pool; int /*<<< orphan*/  start_revision; int /*<<< orphan*/  p2l_checksum; int /*<<< orphan*/  p2l_offset; int /*<<< orphan*/  l2p_checksum; int /*<<< orphan*/  file; int /*<<< orphan*/  block_size; } ;
typedef  TYPE_2__ svn_fs_fs__revision_file_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  footer_length ;
typedef  int apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_END ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_fs__parse_footer (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_aligned_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_read_full2 (int /*<<< orphan*/ ,unsigned char*,unsigned char,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_stringbuf_create_ensure (unsigned char,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_fs_fs__auto_read_footer(svn_fs_fs__revision_file_t *file)
{
  if (file->l2p_offset == -1)
    {
      apr_off_t filesize = 0;
      unsigned char footer_length;
      svn_stringbuf_t *footer;

      /* Determine file size. */
      SVN_ERR(svn_io_file_seek(file->file, APR_END, &filesize, file->pool));

      /* Read last byte (containing the length of the footer). */
      SVN_ERR(svn_io_file_aligned_seek(file->file, file->block_size, NULL,
                                       filesize - 1, file->pool));
      SVN_ERR(svn_io_file_read_full2(file->file, &footer_length,
                                     sizeof(footer_length), NULL, NULL,
                                     file->pool));

      /* Read footer. */
      footer = svn_stringbuf_create_ensure(footer_length, file->pool);
      SVN_ERR(svn_io_file_aligned_seek(file->file, file->block_size, NULL,
                                       filesize - 1 - footer_length,
                                       file->pool));
      SVN_ERR(svn_io_file_read_full2(file->file, footer->data, footer_length,
                                     &footer->len, NULL, file->pool));
      footer->data[footer->len] = '\0';

      /* Extract index locations. */
      SVN_ERR(svn_fs_fs__parse_footer(&file->l2p_offset, &file->l2p_checksum,
                                      &file->p2l_offset, &file->p2l_checksum,
                                      footer, file->start_revision,
                                      filesize - footer_length - 1,
                                      file->pool));
      file->footer_offset = filesize - footer_length - 1;
    }

  return SVN_NO_ERROR;
}