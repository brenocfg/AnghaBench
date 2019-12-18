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
struct ui_file {int dummy; } ;
struct objfile {int minimal_symbol_count; int /*<<< orphan*/  obfd; struct minimal_symbol* msymbols; int /*<<< orphan*/  name; } ;
struct minimal_symbol {int type; int filename; } ;

/* Variables and functions */
 int /*<<< orphan*/ * DEPRECATED_SYMBOL_NAME (struct minimal_symbol*) ; 
 scalar_t__ SYMBOL_BFD_SECTION (struct minimal_symbol*) ; 
 int /*<<< orphan*/ * SYMBOL_DEMANGLED_NAME (struct minimal_symbol*) ; 
 int /*<<< orphan*/  SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 int /*<<< orphan*/  bfd_section_name (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
#define  mst_abs 136 
#define  mst_bss 135 
#define  mst_data 134 
#define  mst_file_bss 133 
#define  mst_file_data 132 
#define  mst_file_text 131 
#define  mst_solib_trampoline 130 
#define  mst_text 129 
#define  mst_unknown 128 
 int /*<<< orphan*/  print_address_numeric (int /*<<< orphan*/ ,int,struct ui_file*) ; 
 int /*<<< orphan*/  warning (char*,int,int) ; 

__attribute__((used)) static void
dump_msymbols (struct objfile *objfile, struct ui_file *outfile)
{
  struct minimal_symbol *msymbol;
  int index;
  char ms_type;

  fprintf_filtered (outfile, "\nObject file %s:\n\n", objfile->name);
  if (objfile->minimal_symbol_count == 0)
    {
      fprintf_filtered (outfile, "No minimal symbols found.\n");
      return;
    }
  for (index = 0, msymbol = objfile->msymbols;
       DEPRECATED_SYMBOL_NAME (msymbol) != NULL; msymbol++, index++)
    {
      switch (msymbol->type)
	{
	case mst_unknown:
	  ms_type = 'u';
	  break;
	case mst_text:
	  ms_type = 'T';
	  break;
	case mst_solib_trampoline:
	  ms_type = 'S';
	  break;
	case mst_data:
	  ms_type = 'D';
	  break;
	case mst_bss:
	  ms_type = 'B';
	  break;
	case mst_abs:
	  ms_type = 'A';
	  break;
	case mst_file_text:
	  ms_type = 't';
	  break;
	case mst_file_data:
	  ms_type = 'd';
	  break;
	case mst_file_bss:
	  ms_type = 'b';
	  break;
	default:
	  ms_type = '?';
	  break;
	}
      fprintf_filtered (outfile, "[%2d] %c ", index, ms_type);
      print_address_numeric (SYMBOL_VALUE_ADDRESS (msymbol), 1, outfile);
      fprintf_filtered (outfile, " %s", DEPRECATED_SYMBOL_NAME (msymbol));
      if (SYMBOL_BFD_SECTION (msymbol))
	fprintf_filtered (outfile, " section %s",
			  bfd_section_name (objfile->obfd,
					    SYMBOL_BFD_SECTION (msymbol)));
      if (SYMBOL_DEMANGLED_NAME (msymbol) != NULL)
	{
	  fprintf_filtered (outfile, "  %s", SYMBOL_DEMANGLED_NAME (msymbol));
	}
#ifdef SOFUN_ADDRESS_MAYBE_MISSING
      if (msymbol->filename)
	fprintf_filtered (outfile, "  %s", msymbol->filename);
#endif
      fputs_filtered ("\n", outfile);
    }
  if (objfile->minimal_symbol_count != index)
    {
      warning ("internal error:  minimal symbol count %d != %d",
	       objfile->minimal_symbol_count, index);
    }
  fprintf_filtered (outfile, "\n");
}