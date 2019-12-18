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
typedef  int /*<<< orphan*/  u_long ;
struct fuzz {scalar_t__ strategies; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUZZ_DBG (char*) ; 
 scalar_t__ fuzz_strategy_done (struct fuzz*) ; 

int
fuzz_done(struct fuzz *fuzz)
{
	FUZZ_DBG(("fuzz = %p, strategies = 0x%lx", fuzz,
	    (u_long)fuzz->strategies));

	return fuzz_strategy_done(fuzz) && fuzz->strategies == 0;
}