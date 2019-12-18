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
struct varobj {int index; int num_children; scalar_t__ updated; int /*<<< orphan*/ * root; scalar_t__ format; int /*<<< orphan*/ * children; int /*<<< orphan*/ * parent; scalar_t__ error; int /*<<< orphan*/ * value; int /*<<< orphan*/ * type; int /*<<< orphan*/ * obj_name; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static struct varobj *
new_variable (void)
{
  struct varobj *var;

  var = (struct varobj *) xmalloc (sizeof (struct varobj));
  var->name = NULL;
  var->obj_name = NULL;
  var->index = -1;
  var->type = NULL;
  var->value = NULL;
  var->error = 0;
  var->num_children = -1;
  var->parent = NULL;
  var->children = NULL;
  var->format = 0;
  var->root = NULL;
  var->updated = 0;

  return var;
}