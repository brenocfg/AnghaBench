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
typedef  char* strchr ;

/* Variables and functions */
 int keypad_final (char const*) ; 

__attribute__((used)) static long
keypad_index(const char *string)
{
    char *test;
    const char *list = "PQRSwxymtuvlqrsPpn";	/* app-keypad except "Enter" */
    int ch;
    long result = -1;

    if ((ch = keypad_final(string)) != '\0') {
	test = (strchr) (list, ch);
	if (test != 0)
	    result = (long) (test - list);
    }
    return result;
}