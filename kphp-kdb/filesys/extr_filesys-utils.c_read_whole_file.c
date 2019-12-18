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
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int read (int,unsigned char*,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 
 unsigned char* zmalloc (int) ; 

__attribute__((used)) static unsigned char *read_whole_file (const char *path, int l) {
  int fd = open (path, O_RDONLY);
  if (fd < 0) {
    vkprintf (1, "Couldn't open %s for reading. %m\n", path);
    return NULL;
  }
  unsigned char *p = zmalloc (l > 0 ? l : 1);
  int bytes_read = read (fd, p, l);
  close (fd);
  if (bytes_read != l) {
    vkprintf (1, "read %d bytes of %d from %s. %m\n", bytes_read, l, path);
    return NULL;
  }
  return p;
}