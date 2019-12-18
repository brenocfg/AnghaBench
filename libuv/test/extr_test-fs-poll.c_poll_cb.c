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
typedef  int /*<<< orphan*/  zero_statbuf ;
typedef  int /*<<< orphan*/  uv_stat_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  int /*<<< orphan*/  uv_fs_poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  FIXTURE ; 
 int UV_ENOENT ; 
 int /*<<< orphan*/  close_cb ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  poll_cb_called ; 
 int /*<<< orphan*/  poll_handle ; 
 int /*<<< orphan*/  remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_cb ; 
 int /*<<< orphan*/  timer_handle ; 
 int /*<<< orphan*/  touch_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uv_is_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_timer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void poll_cb(uv_fs_poll_t* handle,
                    int status,
                    const uv_stat_t* prev,
                    const uv_stat_t* curr) {
  uv_stat_t zero_statbuf;

  memset(&zero_statbuf, 0, sizeof(zero_statbuf));

  ASSERT(handle == &poll_handle);
  ASSERT(1 == uv_is_active((uv_handle_t*) handle));
  ASSERT(prev != NULL);
  ASSERT(curr != NULL);

  switch (poll_cb_called++) {
  case 0:
    ASSERT(status == UV_ENOENT);
    ASSERT(0 == memcmp(prev, &zero_statbuf, sizeof(zero_statbuf)));
    ASSERT(0 == memcmp(curr, &zero_statbuf, sizeof(zero_statbuf)));
    touch_file(FIXTURE);
    break;

  case 1:
    ASSERT(status == 0);
    ASSERT(0 == memcmp(prev, &zero_statbuf, sizeof(zero_statbuf)));
    ASSERT(0 != memcmp(curr, &zero_statbuf, sizeof(zero_statbuf)));
    ASSERT(0 == uv_timer_start(&timer_handle, timer_cb, 20, 0));
    break;

  case 2:
    ASSERT(status == 0);
    ASSERT(0 != memcmp(prev, &zero_statbuf, sizeof(zero_statbuf)));
    ASSERT(0 != memcmp(curr, &zero_statbuf, sizeof(zero_statbuf)));
    ASSERT(0 == uv_timer_start(&timer_handle, timer_cb, 200, 0));
    break;

  case 3:
    ASSERT(status == 0);
    ASSERT(0 != memcmp(prev, &zero_statbuf, sizeof(zero_statbuf)));
    ASSERT(0 != memcmp(curr, &zero_statbuf, sizeof(zero_statbuf)));
    remove(FIXTURE);
    break;

  case 4:
    ASSERT(status == UV_ENOENT);
    ASSERT(0 != memcmp(prev, &zero_statbuf, sizeof(zero_statbuf)));
    ASSERT(0 == memcmp(curr, &zero_statbuf, sizeof(zero_statbuf)));
    uv_close((uv_handle_t*)handle, close_cb);
    break;

  default:
    ASSERT(0);
  }
}