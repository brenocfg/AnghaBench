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
typedef  int uint8_t ;

/* Variables and functions */
 char* find_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rev_compl ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*) ; 

__attribute__((used)) static void
convert_sff_rev_compliance(char *buf, size_t size, uint8_t value)
{
	const char *x;

	if (value > 0x07)
		x = "Unallocated";
	else
		x = find_value(rev_compl, value);

	snprintf(buf, size, "%s", x);
}