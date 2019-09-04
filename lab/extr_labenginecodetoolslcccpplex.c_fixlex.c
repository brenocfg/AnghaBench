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
 size_t COM1 ; 
 scalar_t__ Cplusplus ; 
 int /*<<< orphan*/ ** bigfsm ; 

void
fixlex(void)
{
	/* do C++ comments? */
	if (Cplusplus==0)
		bigfsm['/'][COM1] = bigfsm['x'][COM1];
}