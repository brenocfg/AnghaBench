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
 int ESC_EOL ; 
 int ESC_FON ; 
 int escflags ; 
 int /*<<< orphan*/  outcount ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static void
md_named(const char *s)
{
	printf("&%s;", s);
	escflags &= ~(ESC_FON | ESC_EOL);
	outcount++;
}