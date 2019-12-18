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
struct symtab {char* filename; } ;
struct symbol {int dummy; } ;
typedef  scalar_t__ domain_enum ;

/* Variables and functions */
 scalar_t__ LOC_TYPEDEF ; 
 int STATIC_BLOCK ; 
 scalar_t__ STRUCT_DOMAIN ; 
 scalar_t__ SYMBOL_CLASS (struct symbol*) ; 
 scalar_t__ SYMBOL_DOMAIN (struct symbol*) ; 
 char* SYMBOL_PRINT_NAME (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_TYPE (struct symbol*) ; 
 scalar_t__ TYPES_DOMAIN ; 
 int /*<<< orphan*/  fputs_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  printf_filtered (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  type_print (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typedef_print (int /*<<< orphan*/ ,struct symbol*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_symbol_info (domain_enum kind, struct symtab *s, struct symbol *sym,
		   int block, char *last)
{
  if (last == NULL || strcmp (last, s->filename) != 0)
    {
      fputs_filtered ("\nFile ", gdb_stdout);
      fputs_filtered (s->filename, gdb_stdout);
      fputs_filtered (":\n", gdb_stdout);
    }

  if (kind != TYPES_DOMAIN && block == STATIC_BLOCK)
    printf_filtered ("static ");

  /* Typedef that is not a C++ class */
  if (kind == TYPES_DOMAIN
      && SYMBOL_DOMAIN (sym) != STRUCT_DOMAIN)
    typedef_print (SYMBOL_TYPE (sym), sym, gdb_stdout);
  /* variable, func, or typedef-that-is-c++-class */
  else if (kind < TYPES_DOMAIN ||
	   (kind == TYPES_DOMAIN &&
	    SYMBOL_DOMAIN (sym) == STRUCT_DOMAIN))
    {
      type_print (SYMBOL_TYPE (sym),
		  (SYMBOL_CLASS (sym) == LOC_TYPEDEF
		   ? "" : SYMBOL_PRINT_NAME (sym)),
		  gdb_stdout, 0);

      printf_filtered (";\n");
    }
}