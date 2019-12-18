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
struct type {int dummy; } ;
typedef  enum type_code { ____Placeholder_type_code } type_code ;

/* Variables and functions */
 int TYPE_CODE (struct type*) ; 
 int TYPE_CODE_PTR ; 
 int TYPE_CODE_REF ; 

__attribute__((used)) static int
is_pointer_like (struct type *type)
{
  enum type_code code = TYPE_CODE (type);

  return (code == TYPE_CODE_PTR
          || code == TYPE_CODE_REF);
}