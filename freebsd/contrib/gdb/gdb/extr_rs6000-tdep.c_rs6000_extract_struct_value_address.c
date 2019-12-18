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
struct regcache {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */

__attribute__((used)) static CORE_ADDR
rs6000_extract_struct_value_address (struct regcache *regcache)
{
  /* FIXME: cagney/2002-09-26: PR gdb/724: When making an inferior
     function call GDB knows the address of the struct return value
     and hence, should not need to call this function.  Unfortunately,
     the current call_function_by_hand() code only saves the most
     recent struct address leading to occasional calls.  The code
     should instead maintain a stack of such addresses (in the dummy
     frame object).  */
  /* NOTE: cagney/2002-09-26: Return 0 which indicates that we've
     really got no idea where the return value is being stored.  While
     r3, on function entry, contained the address it will have since
     been reused (scratch) and hence wouldn't be valid */
  return 0;
}