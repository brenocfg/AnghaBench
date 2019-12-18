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
struct symbol_search {int /*<<< orphan*/ * msymbol; TYPE_1__* symtab; int /*<<< orphan*/  block; int /*<<< orphan*/ * symbol; struct symbol_search* next; } ;
struct cleanup {int dummy; } ;
struct TYPE_2__ {char* filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUNCTIONS_DOMAIN ; 
 char* SYMBOL_LINKAGE_NAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYMBOL_PRINT_NAME (int /*<<< orphan*/ *) ; 
 char* alloca (scalar_t__) ; 
 int /*<<< orphan*/  break_command (char*,int) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct cleanup* make_cleanup_free_search_symbols (struct symbol_search*) ; 
 int /*<<< orphan*/  print_symbol_info (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  search_symbols (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,struct symbol_search**) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void
rbreak_command (char *regexp, int from_tty)
{
  struct symbol_search *ss;
  struct symbol_search *p;
  struct cleanup *old_chain;

  search_symbols (regexp, FUNCTIONS_DOMAIN, 0, (char **) NULL, &ss);
  old_chain = make_cleanup_free_search_symbols (ss);

  for (p = ss; p != NULL; p = p->next)
    {
      if (p->msymbol == NULL)
	{
	  char *string = alloca (strlen (p->symtab->filename)
				 + strlen (SYMBOL_LINKAGE_NAME (p->symbol))
				 + 4);
	  strcpy (string, p->symtab->filename);
	  strcat (string, ":'");
	  strcat (string, SYMBOL_LINKAGE_NAME (p->symbol));
	  strcat (string, "'");
	  break_command (string, from_tty);
	  print_symbol_info (FUNCTIONS_DOMAIN,
			     p->symtab,
			     p->symbol,
			     p->block,
			     p->symtab->filename);
	}
      else
	{
	  break_command (SYMBOL_LINKAGE_NAME (p->msymbol), from_tty);
	  printf_filtered ("<function, no debug info> %s;\n",
			   SYMBOL_PRINT_NAME (p->msymbol));
	}
    }

  do_cleanups (old_chain);
}