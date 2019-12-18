#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct varobj {int /*<<< orphan*/  index; int /*<<< orphan*/  parent; TYPE_2__* root; int /*<<< orphan*/ * value; } ;
struct type {int dummy; } ;
struct TYPE_4__ {TYPE_1__* lang; } ;
struct TYPE_3__ {struct type* (* type_of_child ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct type* VALUE_TYPE (int /*<<< orphan*/ *) ; 
 struct type* stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct type *
type_of_child (struct varobj *var)
{

  /* If the child had no evaluation errors, var->value
     will be non-NULL and contain a valid type. */
  if (var->value != NULL)
    return VALUE_TYPE (var->value);

  /* Otherwise, we must compute the type. */
  return (*var->root->lang->type_of_child) (var->parent, var->index);
}