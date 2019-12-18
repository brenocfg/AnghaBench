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
typedef  int /*<<< orphan*/  fp_except ;

/* Variables and functions */
 int /*<<< orphan*/  float_exception_flags ; 

fp_except
fpsetsticky(fp_except except)
{
	fp_except old;

	old = float_exception_flags;
	float_exception_flags = except;
	return old;
}