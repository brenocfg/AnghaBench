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
 int /*<<< orphan*/  isdigit (char const) ; 
 size_t strlen (char const*) ; 

__attribute__((pure)) bool name_is_digits(const char *name) {
    /* positive integers and zero are interpreted as numbers */
    for (size_t i = 0; i < strlen(name); i++)
        if (!isdigit(name[i]))
            return false;

    return true;
}