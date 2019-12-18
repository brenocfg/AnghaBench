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
struct sym_fns {int sym_flavour; struct sym_fns* next; } ;
struct objfile {int /*<<< orphan*/  obfd; struct sym_fns* sf; } ;
typedef  enum bfd_flavour { ____Placeholder_bfd_flavour } bfd_flavour ;

/* Variables and functions */
 int bfd_get_flavour (int /*<<< orphan*/ ) ; 
 char* bfd_get_target (int /*<<< orphan*/ ) ; 
 int bfd_target_ihex_flavour ; 
 int bfd_target_srec_flavour ; 
 int bfd_target_tekhex_flavour ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 struct sym_fns* symtab_fns ; 

__attribute__((used)) static void
find_sym_fns (struct objfile *objfile)
{
  struct sym_fns *sf;
  enum bfd_flavour our_flavour = bfd_get_flavour (objfile->obfd);
  char *our_target = bfd_get_target (objfile->obfd);

  if (our_flavour == bfd_target_srec_flavour
      || our_flavour == bfd_target_ihex_flavour
      || our_flavour == bfd_target_tekhex_flavour)
    return;	/* No symbols. */

  for (sf = symtab_fns; sf != NULL; sf = sf->next)
    {
      if (our_flavour == sf->sym_flavour)
	{
	  objfile->sf = sf;
	  return;
	}
    }
  error ("I'm sorry, Dave, I can't do that.  Symbol format `%s' unknown.",
	 bfd_get_target (objfile->obfd));
}