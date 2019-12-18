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

/* Variables and functions */
 unsigned long CODE_MASK ; 
 unsigned long INV_CODE_MASK ; 
 unsigned long VALID_CODE_MASK ; 

__attribute__((used)) static int
aw_ir_validate_code(unsigned long code)
{
	unsigned long v1, v2;

	/* Don't check address */
	v1 = code & CODE_MASK;
	v2 = (code & INV_CODE_MASK) >> 8;

	if (((v1 ^ v2) & VALID_CODE_MASK) == VALID_CODE_MASK)
		return (0);	/* valid */
	else
		return (1);	/* invalid */
}