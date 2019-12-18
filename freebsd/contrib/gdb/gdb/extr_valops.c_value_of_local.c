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
struct symbol {int dummy; } ;
struct block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_DICT (struct block*) ; 
 struct block* SYMBOL_BLOCK_VALUE (struct symbol*) ; 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 scalar_t__ deprecated_selected_frame ; 
 scalar_t__ dict_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 struct symbol* get_frame_function (scalar_t__) ; 
 struct symbol* lookup_block_symbol (struct block*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct value* read_var_value (struct symbol*,scalar_t__) ; 

struct value *
value_of_local (const char *name, int complain)
{
  struct symbol *func, *sym;
  struct block *b;
  struct value * ret;

  if (deprecated_selected_frame == 0)
    {
      if (complain)
	error ("no frame selected");
      else
	return 0;
    }

  func = get_frame_function (deprecated_selected_frame);
  if (!func)
    {
      if (complain)
	error ("no `%s' in nameless context", name);
      else
	return 0;
    }

  b = SYMBOL_BLOCK_VALUE (func);
  if (dict_empty (BLOCK_DICT (b)))
    {
      if (complain)
	error ("no args, no `%s'", name);
      else
	return 0;
    }

  /* Calling lookup_block_symbol is necessary to get the LOC_REGISTER
     symbol instead of the LOC_ARG one (if both exist).  */
  sym = lookup_block_symbol (b, name, NULL, VAR_DOMAIN);
  if (sym == NULL)
    {
      if (complain)
	error ("current stack frame does not contain a variable named `%s'", name);
      else
	return NULL;
    }

  ret = read_var_value (sym, deprecated_selected_frame);
  if (ret == 0 && complain)
    error ("`%s' argument unreadable", name);
  return ret;
}