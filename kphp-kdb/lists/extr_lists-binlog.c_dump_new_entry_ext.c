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
struct lev_new_entry_ext {int value; int /*<<< orphan*/  extra; int /*<<< orphan*/  object_id; int /*<<< orphan*/  list_id; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dump_int_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dump_list_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_object_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out ; 

void dump_new_entry_ext(FILE *f, const char* szAction, int offset, struct lev_new_entry_ext* E) {
  assert(0 <= offset && offset <= 0xff);
  fprintf(f, "%s+%d\t", szAction, offset);
  dump_list_id(out,E->list_id);
  fputc('\t', out);
  dump_object_id(out,E->object_id);
  fputc('\t', out);
  fprintf(out, "%d\t", E->value);
  dump_int_list(out, E->extra, 4);
  fprintf(out, "\n");
}