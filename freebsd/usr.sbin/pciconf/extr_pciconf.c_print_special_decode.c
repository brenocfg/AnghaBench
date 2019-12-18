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
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_special_decode(bool isa, bool vga, bool subtractive)
{
	bool comma;

	if (isa || vga || subtractive) {
		comma = false;
		printf("    decode     = ");
		if (isa) {
			printf("ISA");
			comma = true;
		}
		if (vga) {
			printf("%sVGA", comma ? ", " : "");
			comma = true;
		}
		if (subtractive)
			printf("%ssubtractive", comma ? ", " : "");
		printf("\n");
	}
}