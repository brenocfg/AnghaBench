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
 int /*<<< orphan*/  lbasename (char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
file_matches (char *file, char *files[], int nfiles)
{
  int i;

  if (file != NULL && nfiles != 0)
    {
      for (i = 0; i < nfiles; i++)
	{
	  if (strcmp (files[i], lbasename (file)) == 0)
	    return 1;
	}
    }
  else if (nfiles == 0)
    return 1;
  return 0;
}