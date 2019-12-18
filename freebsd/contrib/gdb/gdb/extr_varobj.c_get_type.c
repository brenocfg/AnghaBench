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
struct varobj {struct type* type; } ;
struct type {int dummy; } ;

/* Variables and functions */
 struct type* check_typedef (struct type*) ; 

__attribute__((used)) static struct type *
get_type (struct varobj *var)
{
  struct type *type;
  type = var->type;

  if (type != NULL)
    type = check_typedef (type);

  return type;
}