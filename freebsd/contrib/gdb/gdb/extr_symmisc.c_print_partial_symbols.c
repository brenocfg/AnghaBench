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
struct partial_symbol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_SYMBOL_NAME (struct partial_symbol*) ; 
#define  LABEL_DOMAIN 150 
#define  LOC_ARG 149 
#define  LOC_BLOCK 148 
#define  LOC_COMPUTED 147 
#define  LOC_COMPUTED_ARG 146 
#define  LOC_CONST 145 
#define  LOC_CONST_BYTES 144 
#define  LOC_INDIRECT 143 
#define  LOC_LABEL 142 
#define  LOC_LOCAL 141 
#define  LOC_LOCAL_ARG 140 
#define  LOC_OPTIMIZED_OUT 139 
#define  LOC_REF_ARG 138 
#define  LOC_REGISTER 137 
#define  LOC_REGPARM 136 
#define  LOC_REGPARM_ADDR 135 
#define  LOC_STATIC 134 
#define  LOC_TYPEDEF 133 
#define  LOC_UNDEF 132 
#define  LOC_UNRESOLVED 131 
#define  STRUCT_DOMAIN 130 
 int SYMBOL_CLASS (struct partial_symbol*) ; 
 int /*<<< orphan*/ * SYMBOL_DEMANGLED_NAME (struct partial_symbol*) ; 
 int SYMBOL_DOMAIN (struct partial_symbol*) ; 
 int /*<<< orphan*/  SYMBOL_VALUE_ADDRESS (struct partial_symbol*) ; 
#define  UNDEF_DOMAIN 129 
#define  VAR_DOMAIN 128 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 int /*<<< orphan*/  print_address_numeric (int /*<<< orphan*/ ,int,struct ui_file*) ; 

__attribute__((used)) static void
print_partial_symbols (struct partial_symbol **p, int count, char *what,
		       struct ui_file *outfile)
{
  fprintf_filtered (outfile, "  %s partial symbols:\n", what);
  while (count-- > 0)
    {
      fprintf_filtered (outfile, "    `%s'", DEPRECATED_SYMBOL_NAME (*p));
      if (SYMBOL_DEMANGLED_NAME (*p) != NULL)
	{
	  fprintf_filtered (outfile, "  `%s'", SYMBOL_DEMANGLED_NAME (*p));
	}
      fputs_filtered (", ", outfile);
      switch (SYMBOL_DOMAIN (*p))
	{
	case UNDEF_DOMAIN:
	  fputs_filtered ("undefined domain, ", outfile);
	  break;
	case VAR_DOMAIN:
	  /* This is the usual thing -- don't print it */
	  break;
	case STRUCT_DOMAIN:
	  fputs_filtered ("struct domain, ", outfile);
	  break;
	case LABEL_DOMAIN:
	  fputs_filtered ("label domain, ", outfile);
	  break;
	default:
	  fputs_filtered ("<invalid domain>, ", outfile);
	  break;
	}
      switch (SYMBOL_CLASS (*p))
	{
	case LOC_UNDEF:
	  fputs_filtered ("undefined", outfile);
	  break;
	case LOC_CONST:
	  fputs_filtered ("constant int", outfile);
	  break;
	case LOC_STATIC:
	  fputs_filtered ("static", outfile);
	  break;
	case LOC_INDIRECT:
	  fputs_filtered ("extern global", outfile);
	  break;
	case LOC_REGISTER:
	  fputs_filtered ("register", outfile);
	  break;
	case LOC_ARG:
	  fputs_filtered ("pass by value", outfile);
	  break;
	case LOC_REF_ARG:
	  fputs_filtered ("pass by reference", outfile);
	  break;
	case LOC_REGPARM:
	  fputs_filtered ("register parameter", outfile);
	  break;
	case LOC_REGPARM_ADDR:
	  fputs_filtered ("register address parameter", outfile);
	  break;
	case LOC_LOCAL:
	  fputs_filtered ("stack parameter", outfile);
	  break;
	case LOC_TYPEDEF:
	  fputs_filtered ("type", outfile);
	  break;
	case LOC_LABEL:
	  fputs_filtered ("label", outfile);
	  break;
	case LOC_BLOCK:
	  fputs_filtered ("function", outfile);
	  break;
	case LOC_CONST_BYTES:
	  fputs_filtered ("constant bytes", outfile);
	  break;
	case LOC_LOCAL_ARG:
	  fputs_filtered ("shuffled arg", outfile);
	  break;
	case LOC_UNRESOLVED:
	  fputs_filtered ("unresolved", outfile);
	  break;
	case LOC_OPTIMIZED_OUT:
	  fputs_filtered ("optimized out", outfile);
	  break;
	case LOC_COMPUTED:
	case LOC_COMPUTED_ARG:
	  fputs_filtered ("computed at runtime", outfile);
	  break;
	default:
	  fputs_filtered ("<invalid location>", outfile);
	  break;
	}
      fputs_filtered (", ", outfile);
      print_address_numeric (SYMBOL_VALUE_ADDRESS (*p), 1, outfile);
      fprintf_filtered (outfile, "\n");
      p++;
    }
}