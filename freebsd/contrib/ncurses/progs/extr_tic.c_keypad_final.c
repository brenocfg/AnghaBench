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
 scalar_t__ VALID_STRING (char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char
keypad_final(const char *string)
{
    char result = '\0';

    if (VALID_STRING(string)
	&& *string++ == '\033'
	&& *string++ == 'O'
	&& strlen(string) == 1) {
	result = *string;
    }

    return result;
}