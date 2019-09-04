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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int UV_EINVAL ; 
 int UV_ENOBUFS ; 
 int UV_MAXHOSTNAMESIZE ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 scalar_t__ gethostname (char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  uv__once_init () ; 
 int uv_translate_sys_error (int /*<<< orphan*/ ) ; 

int uv_os_gethostname(char* buffer, size_t* size) {
  char buf[UV_MAXHOSTNAMESIZE];
  size_t len;

  if (buffer == NULL || size == NULL || *size == 0)
    return UV_EINVAL;

  uv__once_init(); /* Initialize winsock */

  if (gethostname(buf, sizeof(buf)) != 0)
    return uv_translate_sys_error(WSAGetLastError());

  buf[sizeof(buf) - 1] = '\0'; /* Null terminate, just to be safe. */
  len = strlen(buf);

  if (len >= *size) {
    *size = len + 1;
    return UV_ENOBUFS;
  }

  memcpy(buffer, buf, len + 1);
  *size = len;
  return 0;
}