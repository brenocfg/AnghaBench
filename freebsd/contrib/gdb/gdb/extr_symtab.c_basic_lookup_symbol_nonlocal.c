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
struct symtab {int dummy; } ;
struct symbol {int dummy; } ;
struct block {int dummy; } ;
typedef  int /*<<< orphan*/  domain_enum ;

/* Variables and functions */
 struct symbol* lookup_symbol_global (char const*,char const*,int /*<<< orphan*/  const,struct symtab**) ; 
 struct symbol* lookup_symbol_static (char const*,char const*,struct block const*,int /*<<< orphan*/  const,struct symtab**) ; 

struct symbol *
basic_lookup_symbol_nonlocal (const char *name,
			      const char *linkage_name,
			      const struct block *block,
			      const domain_enum domain,
			      struct symtab **symtab)
{
  struct symbol *sym;

  /* NOTE: carlton/2003-05-19: The comments below were written when
     this (or what turned into this) was part of lookup_symbol_aux;
     I'm much less worried about these questions now, since these
     decisions have turned out well, but I leave these comments here
     for posterity.  */

  /* NOTE: carlton/2002-12-05: There is a question as to whether or
     not it would be appropriate to search the current global block
     here as well.  (That's what this code used to do before the
     is_a_field_of_this check was moved up.)  On the one hand, it's
     redundant with the lookup_symbol_aux_symtabs search that happens
     next.  On the other hand, if decode_line_1 is passed an argument
     like filename:var, then the user presumably wants 'var' to be
     searched for in filename.  On the third hand, there shouldn't be
     multiple global variables all of which are named 'var', and it's
     not like decode_line_1 has ever restricted its search to only
     global variables in a single filename.  All in all, only
     searching the static block here seems best: it's correct and it's
     cleanest.  */

  /* NOTE: carlton/2002-12-05: There's also a possible performance
     issue here: if you usually search for global symbols in the
     current file, then it would be slightly better to search the
     current global block before searching all the symtabs.  But there
     are other factors that have a much greater effect on performance
     than that one, so I don't think we should worry about that for
     now.  */

  sym = lookup_symbol_static (name, linkage_name, block, domain, symtab);
  if (sym != NULL)
    return sym;

  return lookup_symbol_global (name, linkage_name, domain, symtab);
}