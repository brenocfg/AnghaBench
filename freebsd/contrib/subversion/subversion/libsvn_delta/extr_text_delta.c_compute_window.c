#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* tview_len; void* sview_len; int /*<<< orphan*/  sview_offset; } ;
typedef  TYPE_1__ svn_txdelta_window_t ;
struct TYPE_9__ {int /*<<< orphan*/  new_data; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ svn_txdelta__ops_baton_t ;
typedef  int /*<<< orphan*/  svn_filesize_t ;
typedef  void* apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_txdelta__insert_op (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_txdelta__make_window (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_txdelta__xdelta (TYPE_2__*,char const*,void*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_txdelta_new ; 

__attribute__((used)) static svn_txdelta_window_t *
compute_window(const char *data, apr_size_t source_len, apr_size_t target_len,
               svn_filesize_t source_offset, apr_pool_t *pool)
{
  svn_txdelta__ops_baton_t build_baton = { 0 };
  svn_txdelta_window_t *window;

  /* Compute the delta operations. */
  build_baton.new_data = svn_stringbuf_create_empty(pool);

  if (source_len == 0)
    svn_txdelta__insert_op(&build_baton, svn_txdelta_new, 0, target_len, data,
                           pool);
  else
    svn_txdelta__xdelta(&build_baton, data, source_len, target_len, pool);

  /* Create and return the delta window. */
  window = svn_txdelta__make_window(&build_baton, pool);
  window->sview_offset = source_offset;
  window->sview_len = source_len;
  window->tview_len = target_len;
  return window;
}