#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct name_table {int /*<<< orphan*/ * str; int /*<<< orphan*/  val; } ;
struct TYPE_5__ {int /*<<< orphan*/ * cr_rights; } ;
typedef  TYPE_1__ cap_rights_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CAPARSIZE (TYPE_1__*) ; 
 int CAPIDXBIT (int /*<<< orphan*/ ) ; 
 scalar_t__ cap_rights_is_set (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct name_table* caprights ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

void
sysdecode_cap_rights(FILE *fp, cap_rights_t *rightsp)
{
	struct name_table *t;
	int i;
	bool comma;

	for (i = 0; i < CAPARSIZE(rightsp); i++) {
		if (CAPIDXBIT(rightsp->cr_rights[i]) != 1 << i) {
			fprintf(fp, "invalid cap_rights_t");
			return;
		}
	}
	comma = false;
	for (t = caprights; t->str != NULL; t++) {
		if (cap_rights_is_set(rightsp, t->val)) {
			fprintf(fp, "%s%s", comma ? "," : "", t->str);
			comma = true;
		}
	}
}