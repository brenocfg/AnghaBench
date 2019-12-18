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
struct value {int modifiable; } ;
struct internalvar {struct value* value; } ;

/* Variables and functions */
 scalar_t__ VALUE_LAZY (struct value*) ; 
 int /*<<< orphan*/  release_value (struct value*) ; 
 struct value* value_copy (struct value*) ; 
 int /*<<< orphan*/  value_fetch_lazy (struct value*) ; 
 int /*<<< orphan*/  xfree (struct value*) ; 

void
set_internalvar (struct internalvar *var, struct value *val)
{
  struct value *newval;

  newval = value_copy (val);
  newval->modifiable = 1;

  /* Force the value to be fetched from the target now, to avoid problems
     later when this internalvar is referenced and the target is gone or
     has changed.  */
  if (VALUE_LAZY (newval))
    value_fetch_lazy (newval);

  /* Begin code which must not call error().  If var->value points to
     something free'd, an error() obviously leaves a dangling pointer.
     But we also get a danling pointer if var->value points to
     something in the value chain (i.e., before release_value is
     called), because after the error free_all_values will get called before
     long.  */
  xfree (var->value);
  var->value = newval;
  release_value (newval);
  /* End code which must not call error().  */
}