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
typedef  scalar_t__ intmax_t ;
typedef  int /*<<< orphan*/  JSON_Value ;

/* Variables and functions */
 scalar_t__ INT64_MAX ; 
 scalar_t__ INT64_MIN ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  is_decimal (char const*,int) ; 
 int /*<<< orphan*/ * json_value_init_fixed (scalar_t__) ; 
 int /*<<< orphan*/ * json_value_init_number (double) ; 
 double strtod (char const*,char**) ; 
 scalar_t__ strtoimax (char const*,char**,int) ; 

__attribute__((used)) static JSON_Value * parse_number_value(const char **string) {
    char *end;
    double number = 0;
#ifdef JSON_FIXED_NUMBER
    intmax_t fixed;
    errno = 0;
    fixed = strtoimax(*string, &end, 10);
    if (errno == 0 && INT64_MIN <= fixed && fixed <= INT64_MAX && end != NULL &&
			(*end == 0x00 || (*end != '.' && *end != 'e' && *end != 'E'))) {
        *string = end;
        return json_value_init_fixed(fixed);
    }
#endif
    errno = 0;
    number = strtod(*string, &end);
    if (errno || !is_decimal(*string, end - *string)) {
        return NULL;
    }
    *string = end;
    return json_value_init_number(number);
}