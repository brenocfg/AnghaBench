#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_mark_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct mark_apr {int /*<<< orphan*/  off; } ;
struct baton_apr {int /*<<< orphan*/  pool; int /*<<< orphan*/  file; scalar_t__ truncate_on_seek; } ;
typedef  int /*<<< orphan*/  apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SET ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_io_file_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_trunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
seek_handler_apr(void *baton, const svn_stream_mark_t *mark)
{
  struct baton_apr *btn = baton;
  apr_off_t offset = (mark != NULL) ? ((const struct mark_apr *)mark)->off : 0;

  if (btn->truncate_on_seek)
    {
      /* The apr_file_trunc() function always does seek + trunc,
       * and this is documented, so don't seek when truncating. */
      SVN_ERR(svn_io_file_trunc(btn->file, offset, btn->pool));
    }
  else
    {
      SVN_ERR(svn_io_file_seek(btn->file, APR_SET, &offset, btn->pool));
    }

  return SVN_NO_ERROR;
}