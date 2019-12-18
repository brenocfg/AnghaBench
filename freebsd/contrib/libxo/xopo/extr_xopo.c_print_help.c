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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
print_help (void)
{
    fprintf(stderr,
"Usage: xopo [options] format [fields]\n"
"    --help                Display this help text\n"
"    --option <opts> -or -O <opts> Give formatting options\n"
"    --output <file> -or -o <file> Use file as output destination\n"
"    --po <file> or -f <file> Generate new msgid's for a po file\n"
"    --simplify <text> OR -s <text> Show simplified form of the format string\n"
"    --version             Display version information\n"
"    --warn OR -W          Display warnings in text on stderr\n"
);
}