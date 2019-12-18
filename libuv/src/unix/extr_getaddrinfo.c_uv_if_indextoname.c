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
typedef  int /*<<< orphan*/  ifname_buf ;

/* Variables and functions */
 int UV_EINVAL ; 
 int UV_ENOBUFS ; 
 int UV_IF_NAMESIZE ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * if_indextoname (unsigned int,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 size_t strnlen (char*,int) ; 

int uv_if_indextoname(unsigned int ifindex, char* buffer, size_t* size) {
  char ifname_buf[UV_IF_NAMESIZE];
  size_t len;

  if (buffer == NULL || size == NULL || *size == 0)
    return UV_EINVAL;

  if (if_indextoname(ifindex, ifname_buf) == NULL)
    return UV__ERR(errno);

  len = strnlen(ifname_buf, sizeof(ifname_buf));

  if (*size <= len) {
    *size = len + 1;
    return UV_ENOBUFS;
  }

  memcpy(buffer, ifname_buf, len);
  buffer[len] = '\0';
  *size = len;

  return 0;
}