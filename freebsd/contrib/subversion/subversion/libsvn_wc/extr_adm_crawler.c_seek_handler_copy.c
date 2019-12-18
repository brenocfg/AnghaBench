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
struct copying_stream_baton {int /*<<< orphan*/  target; int /*<<< orphan*/  source; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_STREAM_SEEK_NOT_SUPPORTED ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
seek_handler_copy(void *baton, const svn_stream_mark_t *mark)
{
  struct copying_stream_baton *btn = baton;

  /* Only reset support. */
  if (mark)
    {
      return svn_error_create(SVN_ERR_STREAM_SEEK_NOT_SUPPORTED,
                              NULL, NULL);
    }
  else
    {
      SVN_ERR(svn_stream_reset(btn->source));
      SVN_ERR(svn_stream_reset(btn->target));
    }

  return SVN_NO_ERROR;
}