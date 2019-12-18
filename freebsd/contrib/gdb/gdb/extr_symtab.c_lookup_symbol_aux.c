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
struct value {int dummy; } ;
struct symtab {int dummy; } ;
struct symbol {int dummy; } ;
struct block {int dummy; } ;
typedef  int /*<<< orphan*/  domain_enum ;
struct TYPE_2__ {struct symbol* (* la_lookup_symbol_nonlocal ) (char const*,char const*,struct block const*,int /*<<< orphan*/  const,struct symtab**) ;struct value* (* la_value_of_this ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  STATIC_BLOCK ; 
 scalar_t__ check_field (struct value*,char const*) ; 
 TYPE_1__* current_language ; 
 struct symbol* lookup_symbol_aux_local (char const*,char const*,struct block const*,int /*<<< orphan*/  const,struct symtab**) ; 
 struct symbol* lookup_symbol_aux_psymtabs (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/  const,struct symtab**) ; 
 struct symbol* lookup_symbol_aux_symtabs (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/  const,struct symtab**) ; 
 struct value* stub1 (int /*<<< orphan*/ ) ; 
 struct symbol* stub2 (char const*,char const*,struct block const*,int /*<<< orphan*/  const,struct symtab**) ; 

__attribute__((used)) static struct symbol *
lookup_symbol_aux (const char *name, const char *linkage_name,
		   const struct block *block, const domain_enum domain,
		   int *is_a_field_of_this, struct symtab **symtab)
{
  struct symbol *sym;

  /* Make sure we do something sensible with is_a_field_of_this, since
     the callers that set this parameter to some non-null value will
     certainly use it later and expect it to be either 0 or 1.
     If we don't set it, the contents of is_a_field_of_this are
     undefined.  */
  if (is_a_field_of_this != NULL)
    *is_a_field_of_this = 0;

  /* Search specified block and its superiors.  Don't search
     STATIC_BLOCK or GLOBAL_BLOCK.  */

  sym = lookup_symbol_aux_local (name, linkage_name, block, domain,
				 symtab);
  if (sym != NULL)
    return sym;

  /* If requested to do so by the caller and if appropriate for the
     current language, check to see if NAME is a field of `this'. */

  if (current_language->la_value_of_this != NULL
      && is_a_field_of_this != NULL)
    {
      struct value *v = current_language->la_value_of_this (0);

      if (v && check_field (v, name))
	{
	  *is_a_field_of_this = 1;
	  if (symtab != NULL)
	    *symtab = NULL;
	  return NULL;
	}
    }

  /* Now do whatever is appropriate for the current language to look
     up static and global variables.  */

  sym = current_language->la_lookup_symbol_nonlocal (name, linkage_name,
						     block, domain,
						     symtab);
  if (sym != NULL)
    return sym;

  /* Now search all static file-level symbols.  Not strictly correct,
     but more useful than an error.  Do the symtabs first, then check
     the psymtabs.  If a psymtab indicates the existence of the
     desired name as a file-level static, then do psymtab-to-symtab
     conversion on the fly and return the found symbol. */

  sym = lookup_symbol_aux_symtabs (STATIC_BLOCK, name, linkage_name,
				   domain, symtab);
  if (sym != NULL)
    return sym;
  
  sym = lookup_symbol_aux_psymtabs (STATIC_BLOCK, name, linkage_name,
				    domain, symtab);
  if (sym != NULL)
    return sym;

  if (symtab != NULL)
    *symtab = NULL;
  return NULL;
}