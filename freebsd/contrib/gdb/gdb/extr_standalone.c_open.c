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
 int /*<<< orphan*/  EMFILE ; 
 int /*<<< orphan*/  EROFS ; 
 int /*<<< orphan*/  errno ; 
 char* files_start ; 
 char* sourcebeg ; 
 int sourcedesc ; 
 int sourceleft ; 
 char* sourceptr ; 
 int sourcesize ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char*) ; 

open (char *filename, int modes)
{
  char *next;

  if (modes)
    {
      errno = EROFS;
      return -1;
    }

  if (sourceptr)
    {
      errno = EMFILE;
      return -1;
    }

  for (next = files_start; *(int *) next; next += *(int *) next)
    {
      if (!strcmp (next + 4, filename))
	{
	  sourcebeg = next + 4 + strlen (next + 4) + 1;
	  sourcebeg = (char *) (((int) sourcebeg + 3) & (-4));
	  sourceptr = sourcebeg;
	  sourcesize = next + *(int *) next - sourceptr;
	  sourceleft = sourcesize;
	  return sourcedesc;
	}
    }
  return 0;
}