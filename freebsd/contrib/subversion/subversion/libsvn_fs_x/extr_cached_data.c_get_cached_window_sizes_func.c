#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  target_len; scalar_t__ packed_len; } ;
typedef  TYPE_1__ window_sizes_t ;
struct TYPE_8__ {int /*<<< orphan*/  tview_len; } ;
typedef  TYPE_2__ svn_txdelta_window_t ;
struct TYPE_9__ {scalar_t__ start_offset; scalar_t__ end_offset; int /*<<< orphan*/  window; } ;
typedef  TYPE_3__ svn_fs_x__txdelta_cached_window_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* svn_temp_deserializer__ptr (TYPE_3__ const*,void const**) ; 

__attribute__((used)) static svn_error_t *
get_cached_window_sizes_func(void **out,
                             const void *data,
                             apr_size_t data_len,
                             void *baton,
                             apr_pool_t *pool)
{
  const svn_fs_x__txdelta_cached_window_t *window = data;
  const svn_txdelta_window_t *txdelta_window
    = svn_temp_deserializer__ptr(window, (const void **)&window->window);

  window_sizes_t *result = apr_palloc(pool, sizeof(*result));
  result->packed_len = window->end_offset - window->start_offset;
  result->target_len = txdelta_window->tview_len;

  *out = result;

  return SVN_NO_ERROR;
}