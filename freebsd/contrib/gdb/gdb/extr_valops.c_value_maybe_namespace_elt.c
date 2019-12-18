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
struct value {int dummy; } ;
struct type {int dummy; } ;
struct symbol {int dummy; } ;
typedef  enum noside { ____Placeholder_noside } noside ;

/* Variables and functions */
 int EVAL_AVOID_SIDE_EFFECTS ; 
 scalar_t__ LOC_TYPEDEF ; 
 scalar_t__ SYMBOL_CLASS (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_TYPE (struct symbol*) ; 
 char* TYPE_TAG_NAME (struct type const*) ; 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 struct value* allocate_value (int /*<<< orphan*/ ) ; 
 struct symbol* cp_lookup_symbol_namespace (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_selected_block (int /*<<< orphan*/ ) ; 
 struct value* value_of_variable (struct symbol*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct value *
value_maybe_namespace_elt (const struct type *curtype,
			   char *name,
			   enum noside noside)
{
  const char *namespace_name = TYPE_TAG_NAME (curtype);
  struct symbol *sym;

  sym = cp_lookup_symbol_namespace (namespace_name, name, NULL,
				    get_selected_block (0), VAR_DOMAIN,
				    NULL);

  if (sym == NULL)
    return NULL;
  else if ((noside == EVAL_AVOID_SIDE_EFFECTS)
	   && (SYMBOL_CLASS (sym) == LOC_TYPEDEF))
    return allocate_value (SYMBOL_TYPE (sym));
  else
    return value_of_variable (sym, get_selected_block (0));
}