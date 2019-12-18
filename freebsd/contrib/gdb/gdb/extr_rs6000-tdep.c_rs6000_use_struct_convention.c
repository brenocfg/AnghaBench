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

/* Variables and functions */
 int TYPE_LENGTH (struct type*) ; 
 scalar_t__ TYPE_VECTOR (struct type*) ; 

__attribute__((used)) static int     
rs6000_use_struct_convention (int gcc_p, struct type *value_type)
{  
  if ((TYPE_LENGTH (value_type) == 16 || TYPE_LENGTH (value_type) == 8)
      && TYPE_VECTOR (value_type))
    return 0;                            
  return 1;
}