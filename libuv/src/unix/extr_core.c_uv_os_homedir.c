#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  homedir; } ;
typedef  TYPE_1__ uv_passwd_t ;

/* Variables and functions */
 int UV_ENOBUFS ; 
 int UV_ENOENT ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int uv__getpwuid_r (TYPE_1__*) ; 
 int /*<<< orphan*/  uv_os_free_passwd (TYPE_1__*) ; 
 int uv_os_getenv (char*,char*,size_t*) ; 

int uv_os_homedir(char* buffer, size_t* size) {
  uv_passwd_t pwd;
  size_t len;
  int r;

  /* Check if the HOME environment variable is set first. The task of
     performing input validation on buffer and size is taken care of by
     uv_os_getenv(). */
  r = uv_os_getenv("HOME", buffer, size);

  if (r != UV_ENOENT)
    return r;

  /* HOME is not set, so call uv__getpwuid_r() */
  r = uv__getpwuid_r(&pwd);

  if (r != 0) {
    return r;
  }

  len = strlen(pwd.homedir);

  if (len >= *size) {
    *size = len + 1;
    uv_os_free_passwd(&pwd);
    return UV_ENOBUFS;
  }

  memcpy(buffer, pwd.homedir, len + 1);
  *size = len;
  uv_os_free_passwd(&pwd);

  return 0;
}