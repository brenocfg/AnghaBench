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
struct target_ops {int dummy; } ;
struct bfd {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_get_start_address (struct bfd*) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  gdbarch_convert_from_func_ptr_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct target_ops*) ; 

__attribute__((used)) static CORE_ADDR
exec_entry_point (struct bfd *abfd, struct target_ops *targ)
{
  /* KevinB wrote ... for most targets, the address returned by
     bfd_get_start_address() is the entry point for the start
     function.  But, for some targets, bfd_get_start_address() returns
     the address of a function descriptor from which the entry point
     address may be extracted.  This address is extracted by
     gdbarch_convert_from_func_ptr_addr().  The method
     gdbarch_convert_from_func_ptr_addr() is the merely the identify
     function for targets which don't use function descriptors.  */
  return gdbarch_convert_from_func_ptr_addr (current_gdbarch,
					     bfd_get_start_address (abfd),
					     targ);
}