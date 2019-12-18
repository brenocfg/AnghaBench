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
struct baton_apr {int /*<<< orphan*/  pool; int /*<<< orphan*/  file; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct mark_apr* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_io_file_get_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
mark_handler_apr(void *baton, svn_stream_mark_t **mark, apr_pool_t *pool)
{
  struct baton_apr *btn = baton;
  struct mark_apr *mark_apr;

  mark_apr = apr_palloc(pool, sizeof(*mark_apr));
  SVN_ERR(svn_io_file_get_offset(&mark_apr->off, btn->file, btn->pool));
  *mark = (svn_stream_mark_t *)mark_apr;
  return SVN_NO_ERROR;
}