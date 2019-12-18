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
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freelist (char**) ; 
 char* icpyalloc (char*) ; 
 int /*<<< orphan*/ * istrstr (char*,char*) ; 
 scalar_t__ realloc (char*,int) ; 

__attribute__((used)) static char **
enlist (char **cpp, char *new, size_t len)
{
  int i, j;

  if (cpp == NULL)
    return NULL;
  if ((new = icpyalloc(new)) == NULL)
    {
      freelist(cpp);
      return NULL;
    }
  new[len] = '\0';
  /* Is there already something in the list that's new (or longer)? */
  for (i = 0; cpp[i] != NULL; ++i)
    if (istrstr(cpp[i], new) != NULL)
      {
	free(new);
	return cpp;
      }
  /* Eliminate any obsoleted strings. */
  j = 0;
  while (cpp[j] != NULL)
    if (istrstr(new, cpp[j]) == NULL)
      ++j;
    else
      {
	free(cpp[j]);
	if (--i == j)
	  break;
	cpp[j] = cpp[i];
	cpp[i] = NULL;
      }
  /* Add the new string. */
  cpp = (char **) realloc((char *) cpp, (i + 2) * sizeof *cpp);
  if (cpp == NULL)
    return NULL;
  cpp[i] = new;
  cpp[i + 1] = NULL;
  return cpp;
}