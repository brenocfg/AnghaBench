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
typedef  int /*<<< orphan*/  int_values ;

/* Variables and functions */
 int INT_MAX ; 
 int INT_MIN ; 
 scalar_t__ try (char*,int) ; 

__attribute__((used)) static int
cmp_with_sprintf_int (void)
{
    int tot = 0;
    int int_values[] = {INT_MIN, -17, -1, 0, 1, 17, 4711, 65535, INT_MAX};
    int i;

    for (i = 0; i < sizeof(int_values) / sizeof(int_values[0]); ++i) {
	tot += try ("%d", int_values[i]);
	tot += try ("%x", int_values[i]);
	tot += try ("%X", int_values[i]);
	tot += try ("%o", int_values[i]);
	tot += try ("%#x", int_values[i]);
	tot += try ("%#X", int_values[i]);
	tot += try ("%#o", int_values[i]);
	tot += try ("%10d", int_values[i]);
	tot += try ("%10x", int_values[i]);
	tot += try ("%10X", int_values[i]);
	tot += try ("%10o", int_values[i]);
	tot += try ("%#10x", int_values[i]);
	tot += try ("%#10X", int_values[i]);
	tot += try ("%#10o", int_values[i]);
	tot += try ("%-10d", int_values[i]);
	tot += try ("%-10x", int_values[i]);
	tot += try ("%-10X", int_values[i]);
	tot += try ("%-10o", int_values[i]);
	tot += try ("%-#10x", int_values[i]);
	tot += try ("%-#10X", int_values[i]);
	tot += try ("%-#10o", int_values[i]);
    }
    return tot;
}