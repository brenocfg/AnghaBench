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
struct tl_compiler {int /*<<< orphan*/ * expr; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t TL_SECTION_FUNCTIONS ; 
 size_t TL_SECTION_TYPES ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const* const,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int tl_failf (struct tl_compiler*,char*,char const* const) ; 
 int /*<<< orphan*/  tl_write_list_expressions_free_to_file (int /*<<< orphan*/ *,struct tl_compiler*,int /*<<< orphan*/ *) ; 

int tl_write_expressions_to_file (struct tl_compiler *C, const char *const filename) {
  FILE *f = fopen (filename, "w");
  if (f == NULL) {
    return tl_failf (C, "fopen (\"%s\", \"w\") fail. %m", filename);
  }
  tl_write_list_expressions_free_to_file (f, C, &C->expr[TL_SECTION_TYPES]);
  fprintf (f, "---functions---\n");
  tl_write_list_expressions_free_to_file (f, C, &C->expr[TL_SECTION_FUNCTIONS]);
  fclose (f);
  return 0;
}