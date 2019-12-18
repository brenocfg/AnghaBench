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
struct varobj {int dummy; } ;
struct type {int dummy; } ;

/* Variables and functions */
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_PTR ; 
 scalar_t__ TYPE_CODE_REF ; 
 struct type* get_target_type (struct type*) ; 
 struct type* get_type (struct varobj*) ; 

__attribute__((used)) static struct type *
get_type_deref (struct varobj *var)
{
  struct type *type;

  type = get_type (var);

  if (type != NULL && (TYPE_CODE (type) == TYPE_CODE_PTR
		       || TYPE_CODE (type) == TYPE_CODE_REF))
    type = get_target_type (type);

  return type;
}