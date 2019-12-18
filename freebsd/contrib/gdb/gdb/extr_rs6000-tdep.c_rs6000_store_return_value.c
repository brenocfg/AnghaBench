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
struct gdbarch_tdep {scalar_t__ ppc_gp0_regnum; scalar_t__ ppc_vr0_regnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_REGISTER_BYTE (scalar_t__) ; 
 scalar_t__ FP0_REGNUM ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_ARRAY ; 
 scalar_t__ TYPE_CODE_FLT ; 
 int TYPE_LENGTH (struct type*) ; 
 scalar_t__ TYPE_VECTOR (struct type*) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  deprecated_write_register_bytes (int /*<<< orphan*/ ,char*,int) ; 
 struct gdbarch_tdep* gdbarch_tdep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rs6000_store_return_value (struct type *type, char *valbuf)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (current_gdbarch);

  if (TYPE_CODE (type) == TYPE_CODE_FLT)

    /* Floating point values are returned starting from FPR1 and up.
       Say a double_double_double type could be returned in
       FPR1/FPR2/FPR3 triple.  */

    deprecated_write_register_bytes (DEPRECATED_REGISTER_BYTE (FP0_REGNUM + 1), valbuf,
				     TYPE_LENGTH (type));
  else if (TYPE_CODE (type) == TYPE_CODE_ARRAY)
    {
      if (TYPE_LENGTH (type) == 16
          && TYPE_VECTOR (type))
	deprecated_write_register_bytes (DEPRECATED_REGISTER_BYTE (tdep->ppc_vr0_regnum + 2),
					 valbuf, TYPE_LENGTH (type));
    }
  else
    /* Everything else is returned in GPR3 and up.  */
    deprecated_write_register_bytes (DEPRECATED_REGISTER_BYTE (gdbarch_tdep (current_gdbarch)->ppc_gp0_regnum + 3),
				     valbuf, TYPE_LENGTH (type));
}