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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  scalar_t__ svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  inner; int /*<<< orphan*/  fs_path; int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ presentation_stream_baton_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_file_contents (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_file_length (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_from_stringbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stringbuf_from_stream (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
auto_open_inner_stream(presentation_stream_baton_t *b)
{
  if (!b->inner)
    {
      svn_filesize_t length;
      svn_stream_t *stream;
      svn_stringbuf_t *contents;

      SVN_ERR(svn_fs_file_length(&length, b->root, b->fs_path, b->pool));
      SVN_ERR(svn_fs_file_contents(&stream, b->root, b->fs_path, b->pool));
      SVN_ERR(svn_stringbuf_from_stream(&contents, stream,
                                        (apr_size_t)length, b->pool));
      b->inner = svn_stream_from_stringbuf(contents, b->pool);
    }

  return SVN_NO_ERROR;
}