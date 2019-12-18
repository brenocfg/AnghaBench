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
struct vmap {scalar_t__ tstart; scalar_t__ tend; scalar_t__ dstart; struct objfile* objfile; struct vmap* nxt; } ;
struct objfile {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_hex_string (scalar_t__) ; 
 struct objfile* symfile_objfile ; 
 struct vmap* vmap ; 

__attribute__((used)) static CORE_ADDR
find_toc_address (CORE_ADDR pc)
{
  struct vmap *vp;
  extern CORE_ADDR get_toc_offset (struct objfile *);	/* xcoffread.c */

  for (vp = vmap; vp; vp = vp->nxt)
    {
      if (pc >= vp->tstart && pc < vp->tend)
	{
	  /* vp->objfile is only NULL for the exec file.  */
	  return vp->dstart + get_toc_offset (vp->objfile == NULL
					      ? symfile_objfile
					      : vp->objfile);
	}
    }
  error ("Unable to find TOC entry for pc %s\n", local_hex_string (pc));
}