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
struct objfile {int /*<<< orphan*/  obfd; scalar_t__ sym_private; } ;
struct internal_syment {int n_sclass; int n_offset; scalar_t__ n_zeroes; } ;
struct coff_symfile_info {char* debugsec; } ;
struct TYPE_4__ {scalar_t__ local_symesz; } ;
struct TYPE_3__ {struct objfile* objfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_coff_swap_sym_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct internal_syment*) ; 
 TYPE_2__* coff_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  raw_symbol ; 
 int /*<<< orphan*/  symfile_complaints ; 
 int /*<<< orphan*/  symnum ; 
 TYPE_1__* this_symtab_psymtab ; 

__attribute__((used)) static char *
xcoff_next_symbol_text (struct objfile *objfile)
{
  struct internal_syment symbol;
  char *retval;
  /* FIXME: is this the same as the passed arg? */
  objfile = this_symtab_psymtab->objfile;

  bfd_coff_swap_sym_in (objfile->obfd, raw_symbol, &symbol);
  if (symbol.n_zeroes)
    {
      complaint (&symfile_complaints, "Unexpected symbol continuation");

      /* Return something which points to '\0' and hope the symbol reading
         code does something reasonable.  */
      retval = "";
    }
  else if (symbol.n_sclass & 0x80)
    {
      retval =
	((struct coff_symfile_info *) objfile->sym_private)->debugsec
	+ symbol.n_offset;
      raw_symbol +=
	coff_data (objfile->obfd)->local_symesz;
      ++symnum;
    }
  else
    {
      complaint (&symfile_complaints, "Unexpected symbol continuation");

      /* Return something which points to '\0' and hope the symbol reading
         code does something reasonable.  */
      retval = "";
    }
  return retval;
}