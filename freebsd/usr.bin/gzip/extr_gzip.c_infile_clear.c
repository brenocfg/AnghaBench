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
 int /*<<< orphan*/ * infile ; 
 scalar_t__ infile_current ; 
 scalar_t__ infile_total ; 

__attribute__((used)) static	void
infile_clear(void)
{

	infile = NULL;
#ifndef SMALL
	infile_total = infile_current = 0;
#endif
}