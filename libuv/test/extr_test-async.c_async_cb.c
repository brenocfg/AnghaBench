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
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  int /*<<< orphan*/  uv_async_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  async ; 
 int async_cb_called ; 
 int /*<<< orphan*/  close_cb ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  prepare ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void async_cb(uv_async_t* handle) {
  int n;

  ASSERT(handle == &async);

  uv_mutex_lock(&mutex);
  n = ++async_cb_called;
  uv_mutex_unlock(&mutex);

  if (n == 3) {
    uv_close((uv_handle_t*)&async, close_cb);
    uv_close((uv_handle_t*)&prepare, close_cb);
  }
}