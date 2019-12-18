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
 int /*<<< orphan*/  ao_string_cook (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
trim_quotes(char * arg)
{
    switch (*arg) {
    case '"':
    case '\'':
        ao_string_cook(arg, NULL);
    }
    return arg;
}