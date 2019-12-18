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
typedef  void* uint32_t ;
struct ch_reg {void* val; void* addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_SETREG ; 
 scalar_t__ doit (char const*,int /*<<< orphan*/ ,struct ch_reg*) ; 
 int /*<<< orphan*/  err (int,char*) ; 

__attribute__((used)) static void
write_reg(const char *iff_name, uint32_t addr, uint32_t val)
{
	struct ch_reg ch_reg;

	ch_reg.addr = addr;
	ch_reg.val = val;
	
	if (doit(iff_name, CHELSIO_SETREG, &ch_reg) < 0)
		err(1, "register write");
}