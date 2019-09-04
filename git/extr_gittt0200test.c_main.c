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
 char* _ (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 

int main(void)
{
	/* TRANSLATORS: This is a test. You don't need to translate it. */
	puts(_("TEST: A C test string"));

	/* TRANSLATORS: This is a test. You don't need to translate it. */
	printf(_("TEST: A C test string %s"), "variable");

	/* TRANSLATORS: This is a test. You don't need to translate it. */
	printf(_("TEST: Hello World!"));

	/* TRANSLATORS: This is a test. You don't need to translate it. */
	printf(_("TEST: Old English Runes"));

	/* TRANSLATORS: This is a test. You don't need to translate it. */
	printf(_("TEST: ‘single’ and “double” quotes"));
}