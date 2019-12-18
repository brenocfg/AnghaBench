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
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 int sourcedesc ; 
 int sourceleft ; 
 int /*<<< orphan*/  sourceptr ; 

myread (int desc, char *destptr, int size, char *filename)
{
  int len = min (sourceleft, size);

  if (desc != sourcedesc)
    {
      errno = EBADF;
      return -1;
    }

  memcpy (destptr, sourceptr, len);
  sourceleft -= len;
  return len;
}