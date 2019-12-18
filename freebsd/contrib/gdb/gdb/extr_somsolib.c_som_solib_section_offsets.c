#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* data_start; void* text_link_addr; void* text_addr; int /*<<< orphan*/  name; } ;
struct so_list {struct so_list* next; TYPE_1__ som_solib; } ;
struct section_offsets {void** offsets; } ;
struct objfile {int /*<<< orphan*/  obfd; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {void* vma; } ;
typedef  TYPE_2__ asection ;

/* Variables and functions */
 void* ANOFFSET (struct section_offsets*,size_t) ; 
 size_t SECT_OFF_BSS (struct objfile*) ; 
 size_t SECT_OFF_DATA (struct objfile*) ; 
 size_t SECT_OFF_RODATA (struct objfile*) ; 
 size_t SECT_OFF_TEXT (struct objfile*) ; 
 TYPE_2__* bfd_get_section_by_name (int /*<<< orphan*/ ,char*) ; 
 struct so_list* so_list_head ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*) ; 

int
som_solib_section_offsets (struct objfile *objfile,
			   struct section_offsets *offsets)
{
  struct so_list *so_list = so_list_head;

  while (so_list)
    {
      /* Oh what a pain!  We need the offsets before so_list->objfile
         is valid.  The BFDs will never match.  Make a best guess.  */
      if (strstr (objfile->name, so_list->som_solib.name))
	{
	  asection *private_section;

	  /* The text offset is easy.  */
	  offsets->offsets[SECT_OFF_TEXT (objfile)]
	    = (so_list->som_solib.text_addr
	       - so_list->som_solib.text_link_addr);
	  offsets->offsets[SECT_OFF_RODATA (objfile)]
	    = ANOFFSET (offsets, SECT_OFF_TEXT (objfile));

	  /* We should look at presumed_dp in the SOM header, but
	     that's not easily available.  This should be OK though.  */
	  private_section = bfd_get_section_by_name (objfile->obfd,
						     "$PRIVATE$");
	  if (!private_section)
	    {
	      warning ("Unable to find $PRIVATE$ in shared library!");
	      offsets->offsets[SECT_OFF_DATA (objfile)] = 0;
	      offsets->offsets[SECT_OFF_BSS (objfile)] = 0;
	      return 1;
	    }
	  offsets->offsets[SECT_OFF_DATA (objfile)]
	    = (so_list->som_solib.data_start - private_section->vma);
	  offsets->offsets[SECT_OFF_BSS (objfile)]
	    = ANOFFSET (offsets, SECT_OFF_DATA (objfile));
	  return 1;
	}
      so_list = so_list->next;
    }
  return 0;
}