#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct symbol_search {TYPE_1__* symtab; int /*<<< orphan*/  block; int /*<<< orphan*/  symbol; int /*<<< orphan*/ * msymbol; struct symbol_search* next; } ;
struct cleanup {int dummy; } ;
typedef  scalar_t__ domain_enum ;
struct TYPE_2__ {char* filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUIT ; 
 scalar_t__ VARIABLES_DOMAIN ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct cleanup* make_cleanup_free_search_symbols (struct symbol_search*) ; 
 int /*<<< orphan*/  print_msymbol_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_symbol_info (scalar_t__,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  search_symbols (char*,scalar_t__,int /*<<< orphan*/ ,char**,struct symbol_search**) ; 

__attribute__((used)) static void
symtab_symbol_info (char *regexp, domain_enum kind, int from_tty)
{
  static char *classnames[]
  =
  {"variable", "function", "type", "method"};
  struct symbol_search *symbols;
  struct symbol_search *p;
  struct cleanup *old_chain;
  char *last_filename = NULL;
  int first = 1;

  /* must make sure that if we're interrupted, symbols gets freed */
  search_symbols (regexp, kind, 0, (char **) NULL, &symbols);
  old_chain = make_cleanup_free_search_symbols (symbols);

  printf_filtered (regexp
		   ? "All %ss matching regular expression \"%s\":\n"
		   : "All defined %ss:\n",
		   classnames[(int) (kind - VARIABLES_DOMAIN)], regexp);

  for (p = symbols; p != NULL; p = p->next)
    {
      QUIT;

      if (p->msymbol != NULL)
	{
	  if (first)
	    {
	      printf_filtered ("\nNon-debugging symbols:\n");
	      first = 0;
	    }
	  print_msymbol_info (p->msymbol);
	}
      else
	{
	  print_symbol_info (kind,
			     p->symtab,
			     p->symbol,
			     p->block,
			     last_filename);
	  last_filename = p->symtab->filename;
	}
    }

  do_cleanups (old_chain);
}