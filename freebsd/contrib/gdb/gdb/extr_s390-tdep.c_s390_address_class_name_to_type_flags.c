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
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
s390_address_class_name_to_type_flags (struct gdbarch *gdbarch, const char *name,
				       int *type_flags_ptr)
{
  if (strcmp (name, "mode32") == 0)
    {
      *type_flags_ptr = TYPE_FLAG_ADDRESS_CLASS_1;
      return 1;
    }
  else
    return 0;
}