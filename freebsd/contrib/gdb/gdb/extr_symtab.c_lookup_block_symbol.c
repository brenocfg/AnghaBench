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
struct symbol {int dummy; } ;
struct dict_iterator {int dummy; } ;
struct block {int dummy; } ;
typedef  scalar_t__ domain_enum ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_DICT (struct block const*) ; 
 int /*<<< orphan*/  BLOCK_FUNCTION (struct block const*) ; 
 scalar_t__ LOC_ARG ; 
 scalar_t__ LOC_BASEREG_ARG ; 
 scalar_t__ LOC_COMPUTED_ARG ; 
 scalar_t__ LOC_LOCAL_ARG ; 
 scalar_t__ LOC_REF_ARG ; 
 scalar_t__ LOC_REGPARM ; 
 scalar_t__ LOC_REGPARM_ADDR ; 
 scalar_t__ SYMBOL_CLASS (struct symbol*) ; 
 scalar_t__ const SYMBOL_DOMAIN (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_LINKAGE_NAME (struct symbol*) ; 
 struct symbol* dict_iter_name_first (int /*<<< orphan*/ ,char const*,struct dict_iterator*) ; 
 struct symbol* dict_iter_name_next (char const*,struct dict_iterator*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

struct symbol *
lookup_block_symbol (const struct block *block, const char *name,
		     const char *linkage_name,
		     const domain_enum domain)
{
  struct dict_iterator iter;
  struct symbol *sym;

  if (!BLOCK_FUNCTION (block))
    {
      for (sym = dict_iter_name_first (BLOCK_DICT (block), name, &iter);
	   sym != NULL;
	   sym = dict_iter_name_next (name, &iter))
	{
	  if (SYMBOL_DOMAIN (sym) == domain
	      && (linkage_name != NULL
		  ? strcmp (SYMBOL_LINKAGE_NAME (sym), linkage_name) == 0 : 1))
	    return sym;
	}
      return NULL;
    }
  else
    {
      /* Note that parameter symbols do not always show up last in the
	 list; this loop makes sure to take anything else other than
	 parameter symbols first; it only uses parameter symbols as a
	 last resort.  Note that this only takes up extra computation
	 time on a match.  */

      struct symbol *sym_found = NULL;

      for (sym = dict_iter_name_first (BLOCK_DICT (block), name, &iter);
	   sym != NULL;
	   sym = dict_iter_name_next (name, &iter))
	{
	  if (SYMBOL_DOMAIN (sym) == domain
	      && (linkage_name != NULL
		  ? strcmp (SYMBOL_LINKAGE_NAME (sym), linkage_name) == 0 : 1))
	    {
	      sym_found = sym;
	      if (SYMBOL_CLASS (sym) != LOC_ARG &&
		  SYMBOL_CLASS (sym) != LOC_LOCAL_ARG &&
		  SYMBOL_CLASS (sym) != LOC_REF_ARG &&
		  SYMBOL_CLASS (sym) != LOC_REGPARM &&
		  SYMBOL_CLASS (sym) != LOC_REGPARM_ADDR &&
		  SYMBOL_CLASS (sym) != LOC_BASEREG_ARG &&
		  SYMBOL_CLASS (sym) != LOC_COMPUTED_ARG)
		{
		  break;
		}
	    }
	}
      return (sym_found);	/* Will be NULL if not found. */
    }
}