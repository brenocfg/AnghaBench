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
 scalar_t__ BMIPS_GET_CBR () ; 
 scalar_t__ BMIPS_RELO_VECTOR_CONTROL_1 ; 
 int RELO_NORMAL_VEC ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 int ebase ; 
 int kbase ; 

__attribute__((used)) static void kbase_setup(void)
{
	__raw_writel(kbase | RELO_NORMAL_VEC,
		     BMIPS_GET_CBR() + BMIPS_RELO_VECTOR_CONTROL_1);
	ebase = kbase;
}