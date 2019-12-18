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
struct TYPE_3__ {char* ptr; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ uv_fs_t ;
struct stat {int st_size; int /*<<< orphan*/  st_mode; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int lstat (int /*<<< orphan*/ ,struct stat*) ; 
 int os390_readlink (int /*<<< orphan*/ ,char*,int) ; 
 int readlink (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  uv__free (char*) ; 
 int uv__fs_pathmax_size (int /*<<< orphan*/ ) ; 
 char* uv__malloc (int) ; 
 char* uv__realloc (char*,int) ; 

__attribute__((used)) static ssize_t uv__fs_readlink(uv_fs_t* req) {
  ssize_t maxlen;
  ssize_t len;
  char* buf;
  char* newbuf;

#if defined(_POSIX_PATH_MAX) || defined(PATH_MAX)
  maxlen = uv__fs_pathmax_size(req->path);
#else
  /* We may not have a real PATH_MAX.  Read size of link.  */
  struct stat st;
  int ret;
  ret = lstat(req->path, &st);
  if (ret != 0)
    return -1;
  if (!S_ISLNK(st.st_mode)) {
    errno = EINVAL;
    return -1;
  }

  maxlen = st.st_size;

  /* According to readlink(2) lstat can report st_size == 0
     for some symlinks, such as those in /proc or /sys.  */
  if (maxlen == 0)
    maxlen = uv__fs_pathmax_size(req->path);
#endif

  buf = uv__malloc(maxlen);

  if (buf == NULL) {
    errno = ENOMEM;
    return -1;
  }

#if defined(__MVS__)
  len = os390_readlink(req->path, buf, maxlen);
#else
  len = readlink(req->path, buf, maxlen);
#endif

  if (len == -1) {
    uv__free(buf);
    return -1;
  }

  /* Uncommon case: resize to make room for the trailing nul byte. */
  if (len == maxlen) {
    newbuf = uv__realloc(buf, len + 1);

    if (newbuf == NULL) {
      uv__free(buf);
      return -1;
    }

    buf = newbuf;
  }

  buf[len] = '\0';
  req->ptr = buf;

  return 0;
}