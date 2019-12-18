#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_dirent_type_t ;
struct TYPE_3__ {int d_type; } ;
typedef  TYPE_1__ uv__dirent_t ;

/* Variables and functions */
 int /*<<< orphan*/  UV_DIRENT_BLOCK ; 
 int /*<<< orphan*/  UV_DIRENT_CHAR ; 
 int /*<<< orphan*/  UV_DIRENT_DIR ; 
 int /*<<< orphan*/  UV_DIRENT_FIFO ; 
 int /*<<< orphan*/  UV_DIRENT_FILE ; 
 int /*<<< orphan*/  UV_DIRENT_LINK ; 
 int /*<<< orphan*/  UV_DIRENT_SOCKET ; 
 int /*<<< orphan*/  UV_DIRENT_UNKNOWN ; 
#define  UV__DT_BLOCK 134 
#define  UV__DT_CHAR 133 
#define  UV__DT_DIR 132 
#define  UV__DT_FIFO 131 
#define  UV__DT_FILE 130 
#define  UV__DT_LINK 129 
#define  UV__DT_SOCKET 128 

uv_dirent_type_t uv__fs_get_dirent_type(uv__dirent_t* dent) {
  uv_dirent_type_t type;

#ifdef HAVE_DIRENT_TYPES
  switch (dent->d_type) {
    case UV__DT_DIR:
      type = UV_DIRENT_DIR;
      break;
    case UV__DT_FILE:
      type = UV_DIRENT_FILE;
      break;
    case UV__DT_LINK:
      type = UV_DIRENT_LINK;
      break;
    case UV__DT_FIFO:
      type = UV_DIRENT_FIFO;
      break;
    case UV__DT_SOCKET:
      type = UV_DIRENT_SOCKET;
      break;
    case UV__DT_CHAR:
      type = UV_DIRENT_CHAR;
      break;
    case UV__DT_BLOCK:
      type = UV_DIRENT_BLOCK;
      break;
    default:
      type = UV_DIRENT_UNKNOWN;
  }
#else
  type = UV_DIRENT_UNKNOWN;
#endif

  return type;
}