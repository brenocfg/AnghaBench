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
typedef  int /*<<< orphan*/  uv_dirent_type_t ;
typedef  int /*<<< orphan*/  uv__dirent_t ;

/* Variables and functions */
 int /*<<< orphan*/  UV_DIRENT_UNKNOWN ; 

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