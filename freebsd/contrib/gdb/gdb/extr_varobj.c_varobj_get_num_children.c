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
struct varobj {int num_children; } ;

/* Variables and functions */
 int number_of_children (struct varobj*) ; 

int
varobj_get_num_children (struct varobj *var)
{
  if (var->num_children == -1)
    var->num_children = number_of_children (var);

  return var->num_children;
}