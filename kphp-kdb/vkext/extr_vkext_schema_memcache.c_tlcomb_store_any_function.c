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
typedef  int /*<<< orphan*/  zval ;
struct tl_tree {int dummy; } ;
struct tl_combinator {char* id; int /*<<< orphan*/  IP; int /*<<< orphan*/  var_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLUNI_NEXT ; 
 void* TLUNI_START (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ **,struct tl_tree**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ ** get_field (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct tl_tree** get_var_space (struct tl_tree**,int /*<<< orphan*/ ) ; 
 char* parse_zend_string (int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  stderr ; 
 struct tl_combinator* tl_fun_get_by_id (char*) ; 

void *tlcomb_store_any_function (void **IP, void **Data, zval **arr, struct tl_tree **vars) {
  zval **r = get_field (*arr, "_", 0);
  if (!r) { return 0;}
  int l;
  char *s = parse_zend_string (r, &l);
  struct tl_combinator *c = tl_fun_get_by_id (s);
#ifdef VLOG
  fprintf (stderr, "Storing functions %s\n", c->id);
#endif
  if (!c) { return 0; }
  struct tl_tree **new_vars = get_var_space (vars, c->var_num);
  if (!new_vars) {
    return 0;
  }
  void *res = TLUNI_START (c->IP, Data, arr, new_vars);
  if (!res) { return 0; }
  *(Data ++) = res;
  TLUNI_NEXT;
}