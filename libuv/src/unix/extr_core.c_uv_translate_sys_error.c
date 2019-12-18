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

/* Variables and functions */

int uv_translate_sys_error(int sys_errno) {
  /* If < 0 then it's already a libuv error. */
  return sys_errno <= 0 ? sys_errno : -sys_errno;
}