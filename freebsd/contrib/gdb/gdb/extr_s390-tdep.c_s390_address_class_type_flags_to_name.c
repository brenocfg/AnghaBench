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
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int TYPE_FLAG_ADDRESS_CLASS_1 ; 

__attribute__((used)) static const char *
s390_address_class_type_flags_to_name (struct gdbarch *gdbarch, int type_flags)
{
  if (type_flags & TYPE_FLAG_ADDRESS_CLASS_1)
    return "mode32";
  else
    return NULL;
}