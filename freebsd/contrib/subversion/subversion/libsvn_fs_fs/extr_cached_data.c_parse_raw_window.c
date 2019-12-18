#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_10__ {int /*<<< orphan*/  end_offset; int /*<<< orphan*/  window; } ;
typedef  TYPE_3__ svn_fs_fs__txdelta_cached_window_t ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_11__ {int /*<<< orphan*/  end_offset; int /*<<< orphan*/  ver; TYPE_1__ window; } ;
typedef  TYPE_4__ svn_fs_fs__raw_cached_window_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_3__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * svn_stream_from_string (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_temp_deserializer__ptr (TYPE_4__ const*,void const* const*) ; 
 int /*<<< orphan*/  svn_txdelta_read_svndiff_window (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
parse_raw_window(void **out,
                 const void *data,
                 apr_size_t data_len,
                 void *baton,
                 apr_pool_t *result_pool)
{
  svn_string_t raw_window;
  svn_stream_t *stream;

  /* unparsed and parsed window */
  const svn_fs_fs__raw_cached_window_t *window
    = (const svn_fs_fs__raw_cached_window_t *)data;
  svn_fs_fs__txdelta_cached_window_t *result
    = apr_pcalloc(result_pool, sizeof(*result));

  /* create a read stream taking the raw window as input */
  raw_window.data = svn_temp_deserializer__ptr(window,
                                (const void * const *)&window->window.data);
  raw_window.len = window->window.len;
  stream = svn_stream_from_string(&raw_window, result_pool);

  /* parse it */
  SVN_ERR(svn_txdelta_read_svndiff_window(&result->window, stream, window->ver,
                                          result_pool));

  /* complete the window and return it */
  result->end_offset = window->end_offset;
  *out = result;

  return SVN_NO_ERROR;
}