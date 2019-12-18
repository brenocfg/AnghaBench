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
 int MMAN_nl ; 
 int outflags ; 
 int /*<<< orphan*/  print_word (char const*) ; 

__attribute__((used)) static void
print_line(const char *s, int newflags)
{

	outflags |= MMAN_nl;
	print_word(s);
	outflags |= newflags;
}