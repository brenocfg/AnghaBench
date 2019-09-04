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
 int UV_EINVAL ; 

int uv_get_process_title(char* buffer, size_t size) {
  if (buffer == NULL || size == 0)
    return UV_EINVAL;

  buffer[0] = '\0';
  return 0;
}