#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__* new_data; int /*<<< orphan*/  ops; int /*<<< orphan*/  src_ops; int /*<<< orphan*/  num_ops; scalar_t__ tview_len; scalar_t__ sview_len; scalar_t__ sview_offset; } ;
typedef  TYPE_2__ svn_txdelta_window_t ;
struct TYPE_9__ {TYPE_1__* new_data; int /*<<< orphan*/  ops; int /*<<< orphan*/  src_ops; int /*<<< orphan*/  num_ops; } ;
typedef  TYPE_3__ svn_txdelta__ops_baton_t ;
struct TYPE_10__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_4__ svn_string_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 void* apr_palloc (int /*<<< orphan*/ *,int) ; 

svn_txdelta_window_t *
svn_txdelta__make_window(const svn_txdelta__ops_baton_t *build_baton,
                         apr_pool_t *pool)
{
  svn_txdelta_window_t *window;
  svn_string_t *new_data = apr_palloc(pool, sizeof(*new_data));

  window = apr_palloc(pool, sizeof(*window));
  window->sview_offset = 0;
  window->sview_len = 0;
  window->tview_len = 0;

  window->num_ops = build_baton->num_ops;
  window->src_ops = build_baton->src_ops;
  window->ops = build_baton->ops;

  /* just copy the fields over, rather than alloc/copying into a whole new
     svn_string_t structure. */
  /* ### would be much nicer if window->new_data were not a ptr... */
  new_data->data = build_baton->new_data->data;
  new_data->len = build_baton->new_data->len;
  window->new_data = new_data;

  return window;
}