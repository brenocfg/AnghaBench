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
 int CONTENTS_SOLID ; 

int IntersectionContents (int c1, int c2)
{
	int out;

	out = c1 | c2;

	if (out & CONTENTS_SOLID) out = CONTENTS_SOLID;

	return out;
}