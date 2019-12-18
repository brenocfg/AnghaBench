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
struct varobj {char* name; int index; int error; char* obj_name; int /*<<< orphan*/  type; int /*<<< orphan*/  root; struct varobj* parent; int /*<<< orphan*/ * value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPLUS_FAKE_CHILD (struct varobj*) ; 
 int /*<<< orphan*/  install_variable (struct varobj*) ; 
 struct varobj* new_variable () ; 
 int /*<<< orphan*/  save_child_in_parent (struct varobj*,struct varobj*) ; 
 int /*<<< orphan*/  type_of_child (struct varobj*) ; 
 int /*<<< orphan*/ * value_of_child (struct varobj*,int) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char*,char*) ; 

__attribute__((used)) static struct varobj *
create_child (struct varobj *parent, int index, char *name)
{
  struct varobj *child;
  char *childs_name;

  child = new_variable ();

  /* name is allocated by name_of_child */
  child->name = name;
  child->index = index;
  child->value = value_of_child (parent, index);
  if ((!CPLUS_FAKE_CHILD (child) && child->value == NULL) || parent->error)
    child->error = 1;
  child->parent = parent;
  child->root = parent->root;
  xasprintf (&childs_name, "%s.%s", parent->obj_name, name);
  child->obj_name = childs_name;
  install_variable (child);

  /* Save a pointer to this child in the parent */
  save_child_in_parent (parent, child);

  /* Note the type of this child */
  child->type = type_of_child (child);

  return child;
}