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
 char const APOSTROPHE ; 
 int /*<<< orphan*/  QUOT_APOS ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static char const *
print_quoted_apostrophes(char const * str)
{
    while (*str == APOSTROPHE) {
        fputs(QUOT_APOS, stdout);
        str++;
    }
    return str;
}