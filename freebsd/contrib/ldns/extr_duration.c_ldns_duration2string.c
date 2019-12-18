#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ years; scalar_t__ months; scalar_t__ weeks; scalar_t__ days; scalar_t__ hours; scalar_t__ minutes; scalar_t__ seconds; } ;
typedef  TYPE_1__ ldns_duration_type ;

/* Variables and functions */
 scalar_t__ calloc (size_t,int) ; 
 size_t digits_in_number (scalar_t__) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,unsigned int) ; 
 char* strncat (char*,char*,size_t) ; 

char*
ldns_duration2string(const ldns_duration_type* duration)
{
    char* str = NULL, *num = NULL;
    size_t count = 2;
    int T = 0;

    if (!duration) {
        return NULL;
    }

    if (duration->years > 0) {
        count = count + 1 + digits_in_number(duration->years);
    }
    if (duration->months > 0) {
        count = count + 1 + digits_in_number(duration->months);
    }
    if (duration->weeks > 0) {
        count = count + 1 + digits_in_number(duration->weeks);
    }
    if (duration->days > 0) {
        count = count + 1 + digits_in_number(duration->days);
    }
    if (duration->hours > 0) {
        count = count + 1 + digits_in_number(duration->hours);
        T = 1;
    }
    if (duration->minutes > 0) {
        count = count + 1 + digits_in_number(duration->minutes);
        T = 1;
    }
    if (duration->seconds > 0) {
        count = count + 1 + digits_in_number(duration->seconds);
        T = 1;
    }
    if (T) {
        count++;
    }

    str = (char*) calloc(count, sizeof(char));
    str[0] = 'P';
    str[1] = '\0';

    if (duration->years > 0) {
        count = digits_in_number(duration->years);
        num = (char*) calloc(count+2, sizeof(char));
        snprintf(num, count+2, "%uY", (unsigned int) duration->years);
        str = strncat(str, num, count+2);
        free((void*) num);
    }
    if (duration->months > 0) {
        count = digits_in_number(duration->months);
        num = (char*) calloc(count+2, sizeof(char));
        snprintf(num, count+2, "%uM", (unsigned int) duration->months);
        str = strncat(str, num, count+2);
        free((void*) num);
    }
    if (duration->weeks > 0) {
        count = digits_in_number(duration->weeks);
        num = (char*) calloc(count+2, sizeof(char));
        snprintf(num, count+2, "%uW", (unsigned int) duration->weeks);
        str = strncat(str, num, count+2);
        free((void*) num);
    }
    if (duration->days > 0) {
        count = digits_in_number(duration->days);
        num = (char*) calloc(count+2, sizeof(char));
        snprintf(num, count+2, "%uD", (unsigned int) duration->days);
        str = strncat(str, num, count+2);
        free((void*) num);
    }
    if (T) {
        str = strncat(str, "T", 1);
    }
    if (duration->hours > 0) {
        count = digits_in_number(duration->hours);
        num = (char*) calloc(count+2, sizeof(char));
        snprintf(num, count+2, "%uH", (unsigned int) duration->hours);
        str = strncat(str, num, count+2);
        free((void*) num);
    }
    if (duration->minutes > 0) {
        count = digits_in_number(duration->minutes);
        num = (char*) calloc(count+2, sizeof(char));
        snprintf(num, count+2, "%uM", (unsigned int) duration->minutes);
        str = strncat(str, num, count+2);
        free((void*) num);
    }
    if (duration->seconds > 0) {
        count = digits_in_number(duration->seconds);
        num = (char*) calloc(count+2, sizeof(char));
        snprintf(num, count+2, "%uS", (unsigned int) duration->seconds);
        str = strncat(str, num, count+2);
        free((void*) num);
    }
    return str;
}