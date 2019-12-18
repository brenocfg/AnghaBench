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
 scalar_t__ pos ; 
 int string_end ; 
 int string_start ; 
 int /*<<< orphan*/ * string_val ; 

void resetlexer()
{
	string_start = -1;
	string_end = -1;
	string_val = NULL;
	pos = 0;
}