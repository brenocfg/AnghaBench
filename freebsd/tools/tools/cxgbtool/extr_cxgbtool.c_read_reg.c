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
typedef  int /*<<< orphan*/  uint32_t ;
struct ch_reg {int /*<<< orphan*/  val; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_GETREG ; 
 scalar_t__ doit (char const*,int /*<<< orphan*/ ,struct ch_reg*) ; 
 int /*<<< orphan*/  err (int,char*) ; 

__attribute__((used)) static uint32_t
read_reg(const char *iff_name, uint32_t addr)
{
	struct ch_reg reg;

	reg.addr = addr;
	
	if (doit(iff_name, CHELSIO_GETREG, &reg) < 0)
		err(1, "register read");
	return reg.val;
}