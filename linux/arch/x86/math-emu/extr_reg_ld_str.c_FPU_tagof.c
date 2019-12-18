#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int sigh; int sigl; } ;
typedef  TYPE_1__ FPU_REG ;

/* Variables and functions */
 int TAG_Special ; 
 int TAG_Valid ; 
 int TAG_Zero ; 
 int exponent16 (TYPE_1__*) ; 

int FPU_tagof(FPU_REG *ptr)
{
	int exp;

	exp = exponent16(ptr) & 0x7fff;
	if (exp == 0) {
		if (!(ptr->sigh | ptr->sigl)) {
			return TAG_Zero;
		}
		/* The number is a de-normal or pseudodenormal. */
		return TAG_Special;
	}

	if (exp == 0x7fff) {
		/* Is an Infinity, a NaN, or an unsupported data type. */
		return TAG_Special;
	}

	if (!(ptr->sigh & 0x80000000)) {
		/* Unsupported data type. */
		/* Valid numbers have the ms bit set to 1. */
		/* Unnormal. */
		return TAG_Special;
	}

	return TAG_Valid;
}