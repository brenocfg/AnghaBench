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
typedef  int ssize_t ;

/* Variables and functions */
 int UV__PATH_MAX ; 
 int /*<<< orphan*/  _PC_PATH_MAX ; 
 int pathconf (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t uv__fs_pathmax_size(const char* path) {
  ssize_t pathmax;

  pathmax = pathconf(path, _PC_PATH_MAX);

  if (pathmax == -1)
    pathmax = UV__PATH_MAX;

  return pathmax;
}