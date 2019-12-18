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
struct TYPE_3__ {scalar_t__ type; } ;
typedef  TYPE_1__ uv_dirent_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ UV_DIRENT_FILE ; 
 scalar_t__ UV_DIRENT_UNKNOWN ; 

__attribute__((used)) static void assert_is_file_type(uv_dirent_t dent) {
#ifdef HAVE_DIRENT_TYPES
  /*
   * For Apple and Windows, we know getdents is expected to work but for other
   * environments, the filesystem dictates whether or not getdents supports
   * returning the file type.
   *
   *   See:
   *     http://man7.org/linux/man-pages/man2/getdents.2.html
   *     https://github.com/libuv/libuv/issues/501
   */
  #if defined(__APPLE__) || defined(_WIN32)
    ASSERT(dent.type == UV_DIRENT_FILE);
  #else
    ASSERT(dent.type == UV_DIRENT_FILE || dent.type == UV_DIRENT_UNKNOWN);
  #endif
#else
  ASSERT(dent.type == UV_DIRENT_UNKNOWN);
#endif
}