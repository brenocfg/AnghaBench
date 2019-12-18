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
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int TYPE_LENGTH (struct type*) ; 
 scalar_t__ sparc_floating_p (struct type*) ; 
 scalar_t__ sparc_structure_or_union_p (struct type*) ; 

__attribute__((used)) static int
sparc32_stabs_argument_has_addr (struct gdbarch *gdbarch, struct type *type)
{
  return (sparc_structure_or_union_p (type)
	  || (sparc_floating_p (type) && TYPE_LENGTH (type) == 16));
}