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
struct vmap {int loaded; int /*<<< orphan*/  objfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_MASK_ALL ; 
 scalar_t__ catch_errors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  objfile_symbol_add ; 
 int /*<<< orphan*/  vmap_symtab (struct vmap*) ; 

int
vmap_add_symbols (struct vmap *vp)
{
  if (catch_errors (objfile_symbol_add, vp->objfile,
		    "Error while reading shared library symbols:\n",
		    RETURN_MASK_ALL))
    {
      /* Note this is only done if symbol reading was successful.  */
      vp->loaded = 1;
      vmap_symtab (vp);
      return 1;
    }
  return 0;
}