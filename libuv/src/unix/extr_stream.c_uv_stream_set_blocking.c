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
typedef  int /*<<< orphan*/  uv_stream_t ;

/* Variables and functions */
 int uv__nonblock (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uv__stream_fd (int /*<<< orphan*/ *) ; 

int uv_stream_set_blocking(uv_stream_t* handle, int blocking) {
  /* Don't need to check the file descriptor, uv__nonblock()
   * will fail with EBADF if it's not valid.
   */
  return uv__nonblock(uv__stream_fd(handle), !blocking);
}