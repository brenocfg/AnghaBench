#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union internal_auxent {int dummy; } internal_auxent ;
struct objfile {int /*<<< orphan*/  obfd; scalar_t__ sym_private; int /*<<< orphan*/  objfile_obstack; } ;
struct internal_syment {char* n_name; int n_sclass; int n_offset; unsigned int n_numaux; int /*<<< orphan*/  n_type; scalar_t__ n_zeroes; } ;
struct TYPE_3__ {char* e_name; } ;
struct external_syment {TYPE_1__ e; } ;
struct coff_symfile_info {char* debugsec; char* strtbl; } ;
struct TYPE_4__ {int local_symesz; } ;

/* Variables and functions */
 int E_SYMNMLEN ; 
 int /*<<< orphan*/  bfd_coff_swap_aux_in (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int,union internal_auxent*) ; 
 int /*<<< orphan*/  bfd_coff_swap_sym_in (int /*<<< orphan*/ ,char*,struct internal_syment*) ; 
 TYPE_2__* coff_data (int /*<<< orphan*/ ) ; 
 char* obstack_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static void
swap_sym (struct internal_syment *symbol, union internal_auxent *aux,
	  char **name, char **raw, unsigned int *symnump,
	  struct objfile *objfile)
{
  bfd_coff_swap_sym_in (objfile->obfd, *raw, symbol);
  if (symbol->n_zeroes)
    {
      /* If it's exactly E_SYMNMLEN characters long it isn't
         '\0'-terminated.  */
      if (symbol->n_name[E_SYMNMLEN - 1] != '\0')
	{
	  /* FIXME: wastes memory for symbols which we don't end up putting
	     into the minimal symbols.  */
	  char *p;
	  p = obstack_alloc (&objfile->objfile_obstack, E_SYMNMLEN + 1);
	  strncpy (p, symbol->n_name, E_SYMNMLEN);
	  p[E_SYMNMLEN] = '\0';
	  *name = p;
	}
      else
	/* Point to the unswapped name as that persists as long as the
	   objfile does.  */
	*name = ((struct external_syment *) *raw)->e.e_name;
    }
  else if (symbol->n_sclass & 0x80)
    {
      *name = ((struct coff_symfile_info *) objfile->sym_private)->debugsec
	+ symbol->n_offset;
    }
  else
    {
      *name = ((struct coff_symfile_info *) objfile->sym_private)->strtbl
	+ symbol->n_offset;
    }
  ++*symnump;
  *raw += coff_data (objfile->obfd)->local_symesz;
  if (symbol->n_numaux > 0)
    {
      bfd_coff_swap_aux_in (objfile->obfd, *raw, symbol->n_type,
			    symbol->n_sclass, 0, symbol->n_numaux, aux);

      *symnump += symbol->n_numaux;
      *raw += coff_data (objfile->obfd)->local_symesz * symbol->n_numaux;
    }
}