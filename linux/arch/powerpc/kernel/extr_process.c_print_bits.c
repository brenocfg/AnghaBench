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
struct regbit {int bit; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_cont (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_bits(unsigned long val, struct regbit *bits, const char *sep)
{
	const char *s = "";

	for (; bits->bit; ++bits)
		if (val & bits->bit) {
			pr_cont("%s%s", s, bits->name);
			s = sep;
		}
}