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
struct objfile {struct objfile* next; int /*<<< orphan*/ * md; int /*<<< orphan*/  name; int /*<<< orphan*/  objfile_obstack; void* macro_cache; void* psymbol_cache; } ;

/* Variables and functions */
 void* bcache_xmalloc () ; 
 int /*<<< orphan*/  memset (struct objfile*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mstrsave (int /*<<< orphan*/ *,char*) ; 
 struct objfile* object_files ; 
 int /*<<< orphan*/  obstack_init (int /*<<< orphan*/ *) ; 
 struct objfile* rt_common_objfile ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
allocate_rt_common_objfile (void)
{
  struct objfile *objfile;
  struct objfile *last_one;

  objfile = (struct objfile *) xmalloc (sizeof (struct objfile));
  memset (objfile, 0, sizeof (struct objfile));
  objfile->md = NULL;
  objfile->psymbol_cache = bcache_xmalloc ();
  objfile->macro_cache = bcache_xmalloc ();
  obstack_init (&objfile->objfile_obstack);
  objfile->name = mstrsave (objfile->md, "rt_common");

  /* Add this file onto the tail of the linked list of other such files. */

  objfile->next = NULL;
  if (object_files == NULL)
    object_files = objfile;
  else
    {
      for (last_one = object_files;
	   last_one->next;
	   last_one = last_one->next);
      last_one->next = objfile;
    }

  rt_common_objfile = objfile;
}