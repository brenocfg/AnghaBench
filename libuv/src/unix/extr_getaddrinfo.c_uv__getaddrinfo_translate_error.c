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
#define  EAI_ADDRFAMILY 142 
#define  EAI_AGAIN 141 
#define  EAI_BADFLAGS 140 
#define  EAI_BADHINTS 139 
#define  EAI_CANCELED 138 
#define  EAI_FAIL 137 
#define  EAI_FAMILY 136 
#define  EAI_MEMORY 135 
#define  EAI_NODATA 134 
#define  EAI_NONAME 133 
#define  EAI_OVERFLOW 132 
#define  EAI_PROTOCOL 131 
#define  EAI_SERVICE 130 
#define  EAI_SOCKTYPE 129 
#define  EAI_SYSTEM 128 
 int UV_EAI_ADDRFAMILY ; 
 int UV_EAI_AGAIN ; 
 int UV_EAI_BADFLAGS ; 
 int UV_EAI_BADHINTS ; 
 int UV_EAI_CANCELED ; 
 int UV_EAI_FAIL ; 
 int UV_EAI_FAMILY ; 
 int UV_EAI_MEMORY ; 
 int UV_EAI_NODATA ; 
 int UV_EAI_NONAME ; 
 int UV_EAI_OVERFLOW ; 
 int UV_EAI_PROTOCOL ; 
 int UV_EAI_SERVICE ; 
 int UV_EAI_SOCKTYPE ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 

int uv__getaddrinfo_translate_error(int sys_err) {
  switch (sys_err) {
  case 0: return 0;
#if defined(EAI_ADDRFAMILY)
  case EAI_ADDRFAMILY: return UV_EAI_ADDRFAMILY;
#endif
#if defined(EAI_AGAIN)
  case EAI_AGAIN: return UV_EAI_AGAIN;
#endif
#if defined(EAI_BADFLAGS)
  case EAI_BADFLAGS: return UV_EAI_BADFLAGS;
#endif
#if defined(EAI_BADHINTS)
  case EAI_BADHINTS: return UV_EAI_BADHINTS;
#endif
#if defined(EAI_CANCELED)
  case EAI_CANCELED: return UV_EAI_CANCELED;
#endif
#if defined(EAI_FAIL)
  case EAI_FAIL: return UV_EAI_FAIL;
#endif
#if defined(EAI_FAMILY)
  case EAI_FAMILY: return UV_EAI_FAMILY;
#endif
#if defined(EAI_MEMORY)
  case EAI_MEMORY: return UV_EAI_MEMORY;
#endif
#if defined(EAI_NODATA)
  case EAI_NODATA: return UV_EAI_NODATA;
#endif
#if defined(EAI_NONAME)
# if !defined(EAI_NODATA) || EAI_NODATA != EAI_NONAME
  case EAI_NONAME: return UV_EAI_NONAME;
# endif
#endif
#if defined(EAI_OVERFLOW)
  case EAI_OVERFLOW: return UV_EAI_OVERFLOW;
#endif
#if defined(EAI_PROTOCOL)
  case EAI_PROTOCOL: return UV_EAI_PROTOCOL;
#endif
#if defined(EAI_SERVICE)
  case EAI_SERVICE: return UV_EAI_SERVICE;
#endif
#if defined(EAI_SOCKTYPE)
  case EAI_SOCKTYPE: return UV_EAI_SOCKTYPE;
#endif
#if defined(EAI_SYSTEM)
  case EAI_SYSTEM: return UV__ERR(errno);
#endif
  }
  assert(!"unknown EAI_* error code");
  abort();
#ifndef __SUNPRO_C
  return 0;  /* Pacify compiler. */
#endif
}