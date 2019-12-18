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
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char* xmalloc (size_t) ; 
 scalar_t__ xrealloc (char*,int) ; 

__attribute__((used)) static void
add_filename_to_list (const char *fname, char *text, char *word,
		      char ***list, int *list_used, int *list_alloced)
{
  char *new;
  size_t fnlen = strlen (fname);

  if (*list_used + 1 >= *list_alloced)
    {
      *list_alloced *= 2;
      *list = (char **) xrealloc ((char *) *list,
				  *list_alloced * sizeof (char *));
    }

  if (word == text)
    {
      /* Return exactly fname.  */
      new = xmalloc (fnlen + 5);
      strcpy (new, fname);
    }
  else if (word > text)
    {
      /* Return some portion of fname.  */
      new = xmalloc (fnlen + 5);
      strcpy (new, fname + (word - text));
    }
  else
    {
      /* Return some of TEXT plus fname.  */
      new = xmalloc (fnlen + (text - word) + 5);
      strncpy (new, word, text - word);
      new[text - word] = '\0';
      strcat (new, fname);
    }
  (*list)[*list_used] = new;
  (*list)[++*list_used] = NULL;
}