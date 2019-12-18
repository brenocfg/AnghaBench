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
 int openp (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  source_path ; 

int
source_full_path_of (char *filename, char **full_pathname)
{
  int fd;

  fd = openp (source_path, 1, filename, O_RDONLY, 0, full_pathname);
  if (fd < 0)
    {
      *full_pathname = NULL;
      return 0;
    }

  close (fd);
  return 1;
}