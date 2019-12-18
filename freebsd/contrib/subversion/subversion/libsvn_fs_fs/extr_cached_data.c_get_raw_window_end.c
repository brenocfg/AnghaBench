#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  end_offset; } ;
typedef  TYPE_1__ svn_fs_fs__raw_cached_window_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 

__attribute__((used)) static svn_error_t *
get_raw_window_end(void **out,
                   const void *data,
                   apr_size_t data_len,
                   void *baton,
                   apr_pool_t *result_pool)
{
  const svn_fs_fs__raw_cached_window_t *window
    = (const svn_fs_fs__raw_cached_window_t *)data;
  *(apr_off_t*)out = window->end_offset;

  return SVN_NO_ERROR;
}