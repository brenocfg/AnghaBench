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
struct minimal_symbol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 int cache_novlys ; 
 void* cache_ovly_table ; 
 int /*<<< orphan*/  cache_ovly_table_base ; 
 int /*<<< orphan*/  error (char*) ; 
 struct minimal_symbol* lookup_minimal_symbol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int read_memory_integer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_target_long_array (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  simple_free_overlay_table () ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static int
simple_read_overlay_table (void)
{
  struct minimal_symbol *novlys_msym, *ovly_table_msym;

  simple_free_overlay_table ();
  novlys_msym = lookup_minimal_symbol ("_novlys", NULL, NULL);
  if (! novlys_msym)
    {
      error ("Error reading inferior's overlay table: "
             "couldn't find `_novlys' variable\n"
             "in inferior.  Use `overlay manual' mode.");
      return 0;
    }

  ovly_table_msym = lookup_minimal_symbol ("_ovly_table", NULL, NULL);
  if (! ovly_table_msym)
    {
      error ("Error reading inferior's overlay table: couldn't find "
             "`_ovly_table' array\n"
             "in inferior.  Use `overlay manual' mode.");
      return 0;
    }

  cache_novlys = read_memory_integer (SYMBOL_VALUE_ADDRESS (novlys_msym), 4);
  cache_ovly_table
    = (void *) xmalloc (cache_novlys * sizeof (*cache_ovly_table));
  cache_ovly_table_base = SYMBOL_VALUE_ADDRESS (ovly_table_msym);
  read_target_long_array (cache_ovly_table_base,
                          (int *) cache_ovly_table,
                          cache_novlys * 4);

  return 1;			/* SUCCESS */
}