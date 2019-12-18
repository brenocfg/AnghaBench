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
struct ia64_fpreg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ia64_ldf8 (int,struct ia64_fpreg*) ; 
 int /*<<< orphan*/  ia64_stf_spill (struct ia64_fpreg*,int) ; 
 int /*<<< orphan*/  ia64_stop () ; 

__attribute__((used)) static inline void
mem2float_integer (struct ia64_fpreg *init, struct ia64_fpreg *final)
{
	ia64_ldf8(6, init);
	ia64_stop();
	ia64_stf_spill(final, 6);
}