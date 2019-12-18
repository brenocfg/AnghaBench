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
struct stat {int /*<<< orphan*/  st_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  errno ; 
 int sourcedesc ; 
 int /*<<< orphan*/  sourcesize ; 

fstat (int desc, struct stat *statbuf)
{
  if (desc != sourcedesc)
    {
      errno = EBADF;
      return -1;
    }
  statbuf->st_size = sourcesize;
}