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
struct tl_compiler {int flag_reading_builtin_schema; int /*<<< orphan*/ * expr; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 char const* tl_builtin_shema ; 
 int /*<<< orphan*/  tl_compiler_init (struct tl_compiler*) ; 
 int tl_list_expressions_parse (struct tl_compiler*,int /*<<< orphan*/ *) ; 
 int tl_schema_split (struct tl_compiler*,char const*) ; 

int tl_schema_read (struct tl_compiler *C, const char *input) {
  tl_compiler_init (C);
  C->flag_reading_builtin_schema = 1;
  int r = tl_schema_split (C, tl_builtin_shema);
  assert (!r);
  C->flag_reading_builtin_schema = 0;

  r = tl_schema_split (C, input);
  if (r < 0) {
    return r;
  }

  int i;
  for (i = 0; i < 2; i++) {
    r = tl_list_expressions_parse (C, &C->expr[i]);
    if (r < 0) {
      return r;
    }
  }

  return 0;
}