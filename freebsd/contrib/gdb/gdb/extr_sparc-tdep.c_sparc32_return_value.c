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
struct regcache {int dummy; } ;
struct gdbarch {int dummy; } ;
typedef  enum return_value_convention { ____Placeholder_return_value_convention } return_value_convention ;

/* Variables and functions */
 int RETURN_VALUE_REGISTER_CONVENTION ; 
 int RETURN_VALUE_STRUCT_CONVENTION ; 
 int TYPE_LENGTH (struct type*) ; 
 int /*<<< orphan*/  sparc32_extract_return_value (struct type*,struct regcache*,void*) ; 
 int /*<<< orphan*/  sparc32_store_return_value (struct type*,struct regcache*,void const*) ; 
 scalar_t__ sparc_floating_p (struct type*) ; 
 scalar_t__ sparc_structure_or_union_p (struct type*) ; 

__attribute__((used)) static enum return_value_convention
sparc32_return_value (struct gdbarch *gdbarch, struct type *type,
		      struct regcache *regcache, void *readbuf,
		      const void *writebuf)
{
  if (sparc_structure_or_union_p (type)
      || (sparc_floating_p (type) && TYPE_LENGTH (type) == 16))
    return RETURN_VALUE_STRUCT_CONVENTION;

  if (readbuf)
    sparc32_extract_return_value (type, regcache, readbuf);
  if (writebuf)
    sparc32_store_return_value (type, regcache, writebuf);

  return RETURN_VALUE_REGISTER_CONVENTION;
}