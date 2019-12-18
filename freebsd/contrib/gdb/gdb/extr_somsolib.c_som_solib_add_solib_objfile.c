#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ data_start; scalar_t__ text_link_addr; scalar_t__ text_addr; } ;
struct so_list {int /*<<< orphan*/  abfd; TYPE_3__* objfile; TYPE_1__ som_solib; } ;
struct obj_section {int /*<<< orphan*/  endaddr; int /*<<< orphan*/  addr; int /*<<< orphan*/  the_bfd_section; } ;
struct TYPE_5__ {struct so_list* so_info; int /*<<< orphan*/ * unwind_info; } ;
typedef  TYPE_2__ obj_private_data_t ;
typedef  int flagword ;
struct TYPE_6__ {TYPE_2__* obj_private; int /*<<< orphan*/  objfile_obstack; int /*<<< orphan*/  flags; struct obj_section* sections_end; struct obj_section* sections; int /*<<< orphan*/  obfd; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  OBJF_SHARED ; 
 int SEC_CODE ; 
 int SEC_DATA ; 
 int /*<<< orphan*/  bfd_check_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 int bfd_get_section_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_object ; 
 int /*<<< orphan*/  error (char*,char*,char*) ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int) ; 
 TYPE_3__* symbol_file_add (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
som_solib_add_solib_objfile (struct so_list *so, char *name, int from_tty,
			     CORE_ADDR text_addr)
{
  obj_private_data_t *obj_private;
  struct obj_section *s;

  so->objfile = symbol_file_add (name, from_tty, NULL, 0, OBJF_SHARED);
  so->abfd = so->objfile->obfd;

  /* syms_from_objfile has bizarre section offset code,
     so I do my own right here.  */
  for (s = so->objfile->sections; s < so->objfile->sections_end; s++)
    {
      flagword aflag = bfd_get_section_flags(so->abfd, s->the_bfd_section);
      if (aflag & SEC_CODE)
	{
	  s->addr    += so->som_solib.text_addr - so->som_solib.text_link_addr;
	  s->endaddr += so->som_solib.text_addr - so->som_solib.text_link_addr;
	}
      else if (aflag & SEC_DATA)
	{
	  s->addr    += so->som_solib.data_start;
	  s->endaddr += so->som_solib.data_start;
	}
      else
	;
    }
   
  /* Mark this as a shared library and save private data.
   */
  so->objfile->flags |= OBJF_SHARED;

  if (so->objfile->obj_private == NULL)
    {
      obj_private = (obj_private_data_t *)
	obstack_alloc (&so->objfile->objfile_obstack,
		       sizeof (obj_private_data_t));
      obj_private->unwind_info = NULL;
      obj_private->so_info = NULL;
      so->objfile->obj_private = obj_private;
    }

  obj_private = (obj_private_data_t *) so->objfile->obj_private;
  obj_private->so_info = so;

  if (!bfd_check_format (so->abfd, bfd_object))
    {
      error ("\"%s\": not in executable format: %s.",
	     name, bfd_errmsg (bfd_get_error ()));
    }
}