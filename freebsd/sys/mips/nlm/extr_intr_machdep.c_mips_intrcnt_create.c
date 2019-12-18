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
typedef  int /*<<< orphan*/ * mips_intrcnt_t ;

/* Variables and functions */
 int /*<<< orphan*/ * intrcnt ; 
 int /*<<< orphan*/  intrcnt_index ; 
 int /*<<< orphan*/  mips_intrcnt_setname (int /*<<< orphan*/ *,char const*) ; 

mips_intrcnt_t
mips_intrcnt_create(const char* name)
{
	mips_intrcnt_t counter = &intrcnt[intrcnt_index++];

	mips_intrcnt_setname(counter, name);
	return counter;
}