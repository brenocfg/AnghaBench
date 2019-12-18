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
#define  UV_EACCES 134 
#define  UV_EIO 133 
#define  UV_ELOOP 132 
#define  UV_EMFILE 131 
#define  UV_ENFILE 130 
#define  UV_ENOENT 129 
 int UV_ENOSYS ; 
#define  UV_EPERM 128 
 int /*<<< orphan*/  uv__once_init () ; 
 int uv__random_devurandom (void*,size_t) ; 
 int uv__random_getentropy (void*,size_t) ; 
 int uv__random_getrandom (void*,size_t) ; 
 int uv__random_readpath (char*,void*,size_t) ; 
 int uv__random_rtlgenrandom (void*,size_t) ; 
 int uv__random_sysctl (void*,size_t) ; 

__attribute__((used)) static int uv__random(void* buf, size_t buflen) {
  int rc;

#if defined(__PASE__)
  rc = uv__random_readpath("/dev/urandom", buf, buflen);
#elif defined(_AIX)
  rc = uv__random_readpath("/dev/random", buf, buflen);
#elif defined(__APPLE__) || defined(__OpenBSD__) || \
     (defined(__ANDROID_API__) && __ANDROID_API__ >= 28)
  rc = uv__random_getentropy(buf, buflen);
  if (rc == UV_ENOSYS)
    rc = uv__random_devurandom(buf, buflen);
#elif defined(__NetBSD__)
  rc = uv__random_sysctl(buf, buflen);
#elif defined(__FreeBSD__) || defined(__linux__)
  rc = uv__random_getrandom(buf, buflen);
  if (rc == UV_ENOSYS)
    rc = uv__random_devurandom(buf, buflen);
# if defined(__linux__)
  switch (rc) {
    case UV_EACCES:
    case UV_EIO:
    case UV_ELOOP:
    case UV_EMFILE:
    case UV_ENFILE:
    case UV_ENOENT:
    case UV_EPERM:
      rc = uv__random_sysctl(buf, buflen);
      break;
  }
# endif
#elif defined(_WIN32)
  uv__once_init();
  rc = uv__random_rtlgenrandom(buf, buflen);
#else
  rc = uv__random_devurandom(buf, buflen);
#endif

  return rc;
}