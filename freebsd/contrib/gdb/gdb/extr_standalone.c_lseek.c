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
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ sourcebeg ; 
 int sourcedesc ; 
 int sourceleft ; 
 scalar_t__ sourceptr ; 
 int sourcesize ; 

lseek (int desc, int pos)
{

  if (desc != sourcedesc)
    {
      errno = EBADF;
      return -1;
    }

  if (pos < 0 || pos > sourcesize)
    {
      errno = EINVAL;
      return -1;
    }

  sourceptr = sourcebeg + pos;
  sourceleft = sourcesize - pos;
}