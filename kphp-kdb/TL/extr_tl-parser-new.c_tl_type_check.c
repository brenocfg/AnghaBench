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
typedef  int /*<<< orphan*/  tree_var_value_t ;
struct tl_type {int name; int constructors_num; int flags; struct tl_constructor** constructors; int /*<<< orphan*/  id; } ;
struct tl_constructor {int name; char* id; int /*<<< orphan*/  right; } ;

/* Variables and functions */
 int FLAG_EMPTY ; 
 int /*<<< orphan*/  TL_ERROR (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  TL_WARNING (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ __ok ; 
 scalar_t__ check_constructors_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

void tl_type_check (struct tl_type *t) {
  if (!__ok) return;
  if (!strcmp (t->id, "#")) { t->name = 0x70659eff; return; }
  if (!strcmp (t->id, "Type")) { t->name = 0x2cecf817; return; }
  if (t->constructors_num <= 0 && !(t->flags & FLAG_EMPTY)) { 
    TL_ERROR ("Type %s has no constructors\n", t->id);
    __ok = 0;
    return;
  }
  int i, j;
  t->name = 0;
  for (i = 0; i < t->constructors_num; i++) {
    t->name ^= t->constructors[i]->name;
  }
  for (i = 0; i < t->constructors_num; i++) {
    for (j = i + 1; j < t->constructors_num; j++) {
      tree_var_value_t *v = 0;
      if (check_constructors_equal (t->constructors[i]->right, t->constructors[j]->right, &v)) {
        t->flags |= 16;
      }
    }
  }
  if ((t->flags & 24) == 24) {
    TL_WARNING ("Warning: Type %s has overlapping costructors, but it is used with `%%`\n", t->id);   
  }
  int z = 0;
  int sid = 0;
  for (i = 0; i < t->constructors_num; i++) if (*t->constructors[i]->id == '_') {
    z ++;
    sid = i;
  }
  if (z > 1) {
    TL_ERROR ("Type %s has %d default constructors\n", t->id, z);
    __ok = 0;
    return;
  }
  if (z == 1 && (t->flags & 8)) {
    TL_ERROR ("Type %s has default constructors and used bare\n", t->id);
    __ok = 0;
    return;
  }
  if (z) {
    struct tl_constructor *c;
    c = t->constructors[sid];
    t->constructors[sid] = t->constructors[t->constructors_num - 1];
    t->constructors[t->constructors_num - 1] = c;
  }
}