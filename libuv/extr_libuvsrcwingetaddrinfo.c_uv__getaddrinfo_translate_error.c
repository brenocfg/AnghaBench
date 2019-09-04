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
 int UV_EAI_AGAIN ; 
 int UV_EAI_BADFLAGS ; 
 int UV_EAI_FAIL ; 
 int UV_EAI_FAMILY ; 
 int UV_EAI_MEMORY ; 
 int UV_EAI_NONAME ; 
 int UV_EAI_SERVICE ; 
 int UV_EAI_SOCKTYPE ; 
#define  WSAEAFNOSUPPORT 135 
#define  WSAEINVAL 134 
#define  WSAESOCKTNOSUPPORT 133 
#define  WSAHOST_NOT_FOUND 132 
#define  WSANO_RECOVERY 131 
#define  WSATRY_AGAIN 130 
#define  WSATYPE_NOT_FOUND 129 
#define  WSA_NOT_ENOUGH_MEMORY 128 
 int uv_translate_sys_error (int) ; 

int uv__getaddrinfo_translate_error(int sys_err) {
  switch (sys_err) {
    case 0:                       return 0;
    case WSATRY_AGAIN:            return UV_EAI_AGAIN;
    case WSAEINVAL:               return UV_EAI_BADFLAGS;
    case WSANO_RECOVERY:          return UV_EAI_FAIL;
    case WSAEAFNOSUPPORT:         return UV_EAI_FAMILY;
    case WSA_NOT_ENOUGH_MEMORY:   return UV_EAI_MEMORY;
    case WSAHOST_NOT_FOUND:       return UV_EAI_NONAME;
    case WSATYPE_NOT_FOUND:       return UV_EAI_SERVICE;
    case WSAESOCKTNOSUPPORT:      return UV_EAI_SOCKTYPE;
    default:                      return uv_translate_sys_error(sys_err);
  }
}