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
struct type {int dummy; } ;
struct symbol {int dummy; } ;
struct cleanup {int dummy; } ;
typedef  struct symbol* badness_vector ;

/* Variables and functions */
 scalar_t__ STANDARD ; 
 char* alloca (int) ; 
 scalar_t__ classify_oload_match (struct symbol**,int,int /*<<< orphan*/ ) ; 
 scalar_t__ cp_find_first_component (char const*) ; 
 int /*<<< orphan*/  discard_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int find_oload_champ (struct type**,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct symbol**,struct symbol***) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/  (*) (struct symbol**),struct symbol**) ; 
 struct symbol** make_symbol_overload_list (char const*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int /*<<< orphan*/  xfree (struct symbol**) ; 

__attribute__((used)) static int
find_oload_champ_namespace_loop (struct type **arg_types, int nargs,
				 const char *func_name,
				 const char *qualified_name,
				 int namespace_len,
				 struct symbol ***oload_syms,
				 struct badness_vector **oload_champ_bv,
				 int *oload_champ)
{
  int next_namespace_len = namespace_len;
  int searched_deeper = 0;
  int num_fns = 0;
  struct cleanup *old_cleanups;
  int new_oload_champ;
  struct symbol **new_oload_syms;
  struct badness_vector *new_oload_champ_bv;
  char *new_namespace;

  if (next_namespace_len != 0)
    {
      gdb_assert (qualified_name[next_namespace_len] == ':');
      next_namespace_len +=  2;
    }
  next_namespace_len
    += cp_find_first_component (qualified_name + next_namespace_len);

  /* Initialize these to values that can safely be xfree'd.  */
  *oload_syms = NULL;
  *oload_champ_bv = NULL;

  /* First, see if we have a deeper namespace we can search in.  If we
     get a good match there, use it.  */

  if (qualified_name[next_namespace_len] == ':')
    {
      searched_deeper = 1;

      if (find_oload_champ_namespace_loop (arg_types, nargs,
					   func_name, qualified_name,
					   next_namespace_len,
					   oload_syms, oload_champ_bv,
					   oload_champ))
	{
	  return 1;
	}
    };

  /* If we reach here, either we're in the deepest namespace or we
     didn't find a good match in a deeper namespace.  But, in the
     latter case, we still have a bad match in a deeper namespace;
     note that we might not find any match at all in the current
     namespace.  (There's always a match in the deepest namespace,
     because this overload mechanism only gets called if there's a
     function symbol to start off with.)  */

  old_cleanups = make_cleanup (xfree, *oload_syms);
  old_cleanups = make_cleanup (xfree, *oload_champ_bv);
  new_namespace = alloca (namespace_len + 1);
  strncpy (new_namespace, qualified_name, namespace_len);
  new_namespace[namespace_len] = '\0';
  new_oload_syms = make_symbol_overload_list (func_name,
					      new_namespace);
  while (new_oload_syms[num_fns])
    ++num_fns;

  new_oload_champ = find_oload_champ (arg_types, nargs, 0, num_fns,
				      NULL, new_oload_syms,
				      &new_oload_champ_bv);

  /* Case 1: We found a good match.  Free earlier matches (if any),
     and return it.  Case 2: We didn't find a good match, but we're
     not the deepest function.  Then go with the bad match that the
     deeper function found.  Case 3: We found a bad match, and we're
     the deepest function.  Then return what we found, even though
     it's a bad match.  */

  if (new_oload_champ != -1
      && classify_oload_match (new_oload_champ_bv, nargs, 0) == STANDARD)
    {
      *oload_syms = new_oload_syms;
      *oload_champ = new_oload_champ;
      *oload_champ_bv = new_oload_champ_bv;
      do_cleanups (old_cleanups);
      return 1;
    }
  else if (searched_deeper)
    {
      xfree (new_oload_syms);
      xfree (new_oload_champ_bv);
      discard_cleanups (old_cleanups);
      return 0;
    }
  else
    {
      gdb_assert (new_oload_champ != -1);
      *oload_syms = new_oload_syms;
      *oload_champ = new_oload_champ;
      *oload_champ_bv = new_oload_champ_bv;
      discard_cleanups (old_cleanups);
      return 0;
    }
}