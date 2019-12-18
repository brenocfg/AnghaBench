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
typedef  int /*<<< orphan*/  time_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int get_fsize (int,int /*<<< orphan*/ *) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int read (int,unsigned char*,int) ; 
 unsigned char* ztmalloc (int) ; 

__attribute__((used)) static unsigned char *read_whole_file (const char *path, int *l, time_t *mtime) {
  int fd = open (path, O_RDONLY);
  if (fd < 0) {
    return NULL;
  }
  *l = get_fsize (fd, mtime);
  if (*l < 0) {
    close (fd);
    return NULL;
  }
  unsigned char *p = ztmalloc ((*l + 3) & -4);
  int bytes_read = read (fd, p, *l);
  close (fd);
  if (bytes_read != *l) {
    return NULL;
  }
  return p;
}