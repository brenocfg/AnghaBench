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
struct fn_field {int dummy; } ;

/* Variables and functions */
 scalar_t__ TYPE_FN_FIELD_STATIC_P (struct fn_field*,int) ; 

__attribute__((used)) static int
oload_method_static (int method, struct fn_field *fns_ptr, int index)
{
  if (method && TYPE_FN_FIELD_STATIC_P (fns_ptr, index))
    return 1;
  else
    return 0;
}