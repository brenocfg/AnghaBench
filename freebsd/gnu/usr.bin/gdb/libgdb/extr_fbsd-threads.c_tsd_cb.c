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
typedef  int /*<<< orphan*/  thread_key_t ;
struct minimal_symbol {int dummy; } ;

/* Variables and functions */
 char* DEPRECATED_SYMBOL_NAME (struct minimal_symbol*) ; 
 int /*<<< orphan*/  builtin_type_void_func_ptr ; 
 int /*<<< orphan*/  extract_typed_address (void (*) (void*),int /*<<< orphan*/ ) ; 
 struct minimal_symbol* lookup_minimal_symbol_by_pc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ,void (*) (void*),char*) ; 

__attribute__((used)) static int
tsd_cb (thread_key_t key, void (*destructor)(void *), void *ignore)
{
  struct minimal_symbol *ms;
  char *name;

  ms = lookup_minimal_symbol_by_pc (
	extract_typed_address(&destructor, builtin_type_void_func_ptr));
  if (!ms)
    name = "???";
  else
    name = DEPRECATED_SYMBOL_NAME (ms);

  printf_filtered ("Key %d, destructor %p <%s>\n", key, destructor, name);
  return 0;
}