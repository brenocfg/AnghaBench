#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {TYPE_1__ window; } ;
typedef  TYPE_2__ svn_fs_fs__raw_cached_window_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_temp_deserializer__resolve (TYPE_2__*,void**) ; 

svn_error_t *
svn_fs_fs__deserialize_raw_window(void **item,
                                  void *buffer,
                                  apr_size_t buffer_size,
                                  apr_pool_t *pool)
{
  svn_fs_fs__raw_cached_window_t *window =
      (svn_fs_fs__raw_cached_window_t *)buffer;

  /* pointer reference fixup */
  svn_temp_deserializer__resolve(window, (void **)&window->window.data);

  /* done */
  *item = buffer;

  return SVN_NO_ERROR;
}