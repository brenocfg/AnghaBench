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
struct vmap {scalar_t__ tstart; scalar_t__ tend; scalar_t__* member; int /*<<< orphan*/  name; struct vmap* nxt; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 struct vmap* vmap ; 
 int /*<<< orphan*/  xasprintf (char**,char*,int /*<<< orphan*/ ,char*,scalar_t__*,char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 

char *
xcoff_solib_address (CORE_ADDR addr)
{
  static char *buffer = NULL;
  struct vmap *vp = vmap;

  /* The first vmap entry is for the exec file.  */

  if (vp == NULL)
    return NULL;
  for (vp = vp->nxt; vp; vp = vp->nxt)
    if (vp->tstart <= addr && addr < vp->tend)
      {
	xfree (buffer);
	xasprintf (&buffer, "%s%s%s%s",
			    vp->name,
			    *vp->member ? "(" : "",
			    vp->member,
			    *vp->member ? ")" : "");
	return buffer;
      }
  return NULL;
}