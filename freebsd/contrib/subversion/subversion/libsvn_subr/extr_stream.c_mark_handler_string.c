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
struct string_stream_mark {int /*<<< orphan*/  pos; } ;
struct string_stream_baton {int /*<<< orphan*/  amt_read; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct string_stream_mark* apr_palloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static svn_error_t *
mark_handler_string(void *baton, svn_stream_mark_t **mark, apr_pool_t *pool)
{
  struct string_stream_baton *btn;
  struct string_stream_mark *marker;

  btn = baton;

  marker = apr_palloc(pool, sizeof(*marker));
  marker->pos = btn->amt_read;
  *mark = (svn_stream_mark_t *)marker;
  return SVN_NO_ERROR;
}