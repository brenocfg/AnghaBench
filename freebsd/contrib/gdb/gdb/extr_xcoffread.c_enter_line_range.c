#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct subfile {int dummy; } ;
struct TYPE_5__ {scalar_t__ l_paddr; int /*<<< orphan*/  l_symndx; } ;
struct internal_lineno {scalar_t__ l_lnno; TYPE_1__ l_addr; } ;
struct coff_symfile_info {unsigned int max_lineno_offset; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_8__ {int /*<<< orphan*/  section_offsets; int /*<<< orphan*/ * obfd; scalar_t__ sym_private; } ;
struct TYPE_7__ {int local_linesz; } ;
struct TYPE_6__ {TYPE_4__* objfile; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ ANOFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SECT_OFF_TEXT (TYPE_4__*) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 void* alloca (int) ; 
 int /*<<< orphan*/  bfd_bread (void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_coff_swap_lineno_in (int /*<<< orphan*/ *,void*,struct internal_lineno*) ; 
 int /*<<< orphan*/  bfd_seek (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_3__* coff_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*) ; 
 unsigned int read_symbol_lineno (int /*<<< orphan*/ ) ; 
 scalar_t__ read_symbol_nvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  record_line (struct subfile*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  symfile_complaints ; 
 TYPE_2__* this_symtab_psymtab ; 

__attribute__((used)) static void
enter_line_range (struct subfile *subfile, unsigned beginoffset, unsigned endoffset,	/* offsets to line table */
		  CORE_ADDR startaddr,	/* offsets to line table */
		  CORE_ADDR endaddr, unsigned *firstLine)
{
  unsigned int curoffset;
  CORE_ADDR addr;
  void *ext_lnno;
  struct internal_lineno int_lnno;
  unsigned int limit_offset;
  bfd *abfd;
  int linesz;

  if (endoffset == 0 && startaddr == 0 && endaddr == 0)
    return;
  curoffset = beginoffset;
  limit_offset =
    ((struct coff_symfile_info *) this_symtab_psymtab->objfile->sym_private)
    ->max_lineno_offset;

  if (endoffset != 0)
    {
      if (endoffset >= limit_offset)
	{
	  complaint (&symfile_complaints,
		     "Bad line table offset in C_EINCL directive");
	  return;
	}
      limit_offset = endoffset;
    }
  else
    limit_offset -= 1;

  abfd = this_symtab_psymtab->objfile->obfd;
  linesz = coff_data (abfd)->local_linesz;
  ext_lnno = alloca (linesz);

  while (curoffset <= limit_offset)
    {
      bfd_seek (abfd, curoffset, SEEK_SET);
      bfd_bread (ext_lnno, linesz, abfd);
      bfd_coff_swap_lineno_in (abfd, ext_lnno, &int_lnno);

      /* Find the address this line represents.  */
      addr = (int_lnno.l_lnno
	      ? int_lnno.l_addr.l_paddr
	      : read_symbol_nvalue (int_lnno.l_addr.l_symndx));
      addr += ANOFFSET (this_symtab_psymtab->objfile->section_offsets,
			SECT_OFF_TEXT (this_symtab_psymtab->objfile));

      if (addr < startaddr || (endaddr && addr >= endaddr))
	return;

      if (int_lnno.l_lnno == 0)
	{
	  *firstLine = read_symbol_lineno (int_lnno.l_addr.l_symndx);
	  record_line (subfile, 0, addr);
	  --(*firstLine);
	}
      else
	record_line (subfile, *firstLine + int_lnno.l_lnno, addr);
      curoffset += linesz;
    }
}