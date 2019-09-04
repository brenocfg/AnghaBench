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
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  close (int const) ; 
 int creat (char const*,int) ; 
 int hc_path_exist (char const*) ; 
 int /*<<< orphan*/  unlink (char const*) ; 

bool hc_path_create (const char *path)
{
  if (hc_path_exist (path) == true) return false;

  const int fd = creat (path, S_IRUSR | S_IWUSR);

  if (fd == -1) return false;

  close (fd);

  unlink (path);

  return true;
}