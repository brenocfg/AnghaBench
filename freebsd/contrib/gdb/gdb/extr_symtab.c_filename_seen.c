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
 scalar_t__ strcmp (char const*,char const*) ; 
 scalar_t__ xmalloc (int) ; 
 scalar_t__ xrealloc (char*,int) ; 

__attribute__((used)) static int
filename_seen (const char *file, int add, int *first)
{
  /* Table of files seen so far.  */
  static const char **tab = NULL;
  /* Allocated size of tab in elements.
     Start with one 256-byte block (when using GNU malloc.c).
     24 is the malloc overhead when range checking is in effect.  */
  static int tab_alloc_size = (256 - 24) / sizeof (char *);
  /* Current size of tab in elements.  */
  static int tab_cur_size;
  const char **p;

  if (*first)
    {
      if (tab == NULL)
	tab = (const char **) xmalloc (tab_alloc_size * sizeof (*tab));
      tab_cur_size = 0;
    }

  /* Is FILE in tab?  */
  for (p = tab; p < tab + tab_cur_size; p++)
    if (strcmp (*p, file) == 0)
      return 1;

  /* No; maybe add it to tab.  */
  if (add)
    {
      if (tab_cur_size == tab_alloc_size)
	{
	  tab_alloc_size *= 2;
	  tab = (const char **) xrealloc ((char *) tab,
					  tab_alloc_size * sizeof (*tab));
	}
      tab[tab_cur_size++] = file;
    }

  return 0;
}