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
struct lev_set_flags {int type; int /*<<< orphan*/  object_id; int /*<<< orphan*/  list_id; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int LEV_LI_SET_FLAGS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dump_list_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_object_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,int) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 

void dump_set_flags (FILE *f, const char* szAction, int offset, struct lev_set_flags* E) {
  assert(0 <= offset && offset <= 0xff);
  fprintf(f, "%s+%d\t", szAction, E->type-LEV_LI_SET_FLAGS);
  dump_list_id(f,E->list_id);
  fputc('\t', f);
  dump_object_id(f,E->object_id);
  fputc('\n', f);
}