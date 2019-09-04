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
 int UV_ENOBUFS ; 
 int snprintf (char*,size_t,char*,unsigned int) ; 
 int uv_translate_sys_error (int) ; 

int uv_if_indextoiid(unsigned int ifindex, char* buffer, size_t* size) {
  int r;

  if (buffer == NULL || size == NULL || *size == 0)
    return UV_EINVAL;

  r = snprintf(buffer, *size, "%d", ifindex);

  if (r < 0)
    return uv_translate_sys_error(r);

  if (r >= (int) *size) {
    *size = r + 1;
    return UV_ENOBUFS;
  }

  *size = r;
  return 0;
}