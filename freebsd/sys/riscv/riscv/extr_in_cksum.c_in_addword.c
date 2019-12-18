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
typedef  scalar_t__ u_short ;
typedef  scalar_t__ u_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADDCARRY (scalar_t__) ; 

u_short
in_addword(u_short a, u_short b)
{
	u_int64_t sum = a + b;

	ADDCARRY(sum);
	return (sum);
}