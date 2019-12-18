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
 char** addlists (char**,char**) ; 
 char** comsubs (char*,char*) ; 
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/  freelist (char**) ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static char **
inboth (char **left, char **right)
{
  char **both;
  char **temp;
  int lnum, rnum;

  if (left == NULL || right == NULL)
    return NULL;
  both = (char **) malloc(sizeof *both);
  if (both == NULL)
    return NULL;
  both[0] = NULL;
  for (lnum = 0; left[lnum] != NULL; ++lnum)
    {
      for (rnum = 0; right[rnum] != NULL; ++rnum)
	{
	  temp = comsubs(left[lnum], right[rnum]);
	  if (temp == NULL)
	    {
	      freelist(both);
	      return NULL;
	    }
	  both = addlists(both, temp);
	  freelist(temp);
	  free(temp);
	  if (both == NULL)
	    return NULL;
	}
    }
  return both;
}