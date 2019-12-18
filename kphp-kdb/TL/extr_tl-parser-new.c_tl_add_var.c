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
struct tl_var {int type; scalar_t__ flags; struct tl_combinator_tree* ptr; int /*<<< orphan*/  id; } ;
struct tl_combinator_tree {int dummy; } ;

/* Variables and functions */
 struct tl_var** last_num_var ; 
 int /*<<< orphan*/  lrand48 () ; 
 size_t namespace_level ; 
 int /*<<< orphan*/  tree_insert_tl_var (int /*<<< orphan*/ ,struct tl_var*,int /*<<< orphan*/ ) ; 
 scalar_t__ tree_lookup_tl_var (int /*<<< orphan*/ ,struct tl_var*) ; 
 int /*<<< orphan*/ * vars ; 
 int /*<<< orphan*/  vkprintf (int,char*,char*) ; 
 struct tl_var* zmalloc (int) ; 
 int /*<<< orphan*/  zstrdup (char*) ; 

struct tl_var *tl_add_var (char *id, struct tl_combinator_tree *ptr, int type) {
  vkprintf (2, "Add var %s\n", id);
  struct tl_var *v = zmalloc (sizeof (*v));
  v->id = zstrdup (id);
  v->type = type;
  v->ptr = ptr;
  v->flags = 0;
  if (tree_lookup_tl_var (vars[namespace_level], v)) {
    return 0;
  }
  vars[namespace_level] = tree_insert_tl_var (vars[namespace_level], v, lrand48 ());
  if (type) {
    last_num_var[namespace_level] = v;
  }
  return v;
}