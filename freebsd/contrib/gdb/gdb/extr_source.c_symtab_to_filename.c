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
struct symtab {char* fullname; char* filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int open_source_file (struct symtab*) ; 

char *
symtab_to_filename (struct symtab *s)
{
  int fd;

  if (!s)
    return NULL;

  /* If we've seen the file before, just return fullname. */

  if (s->fullname)
    return s->fullname;

  /* Try opening the file to setup fullname */

  fd = open_source_file (s);
  if (fd < 0)
    return s->filename;		/* File not found.  Just use short name */

  /* Found the file.  Cleanup and return the full name */

  close (fd);
  return s->fullname;
}