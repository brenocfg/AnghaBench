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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  uv__close (int) ; 
 int uv__open_cloexec (char const*,int /*<<< orphan*/ ) ; 

FILE* uv__open_file(const char* path) {
  int fd;
  FILE* fp;

  fd = uv__open_cloexec(path, O_RDONLY);
  if (fd < 0)
    return NULL;

   fp = fdopen(fd, "r");
   if (fp == NULL)
     uv__close(fd);

   return fp;
}