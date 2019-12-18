#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* time_t ;
struct TYPE_5__ {void* weeks; void* seconds; void* minutes; void* hours; void* days; void* months; void* years; } ;
typedef  TYPE_1__ ldns_duration_type ;

/* Variables and functions */
 scalar_t__ atoi (char const*) ; 
 int /*<<< orphan*/  ldns_duration_cleanup (TYPE_1__*) ; 
 TYPE_1__* ldns_duration_create () ; 
 char* strchr (char const*,char) ; 
 char* strrchr (char const*,char) ; 

ldns_duration_type*
ldns_duration_create_from_string(const char* str)
{
    ldns_duration_type* duration = ldns_duration_create();
    char* P, *X, *T, *W;
    int not_weeks = 0;

    if (!duration) {
        return NULL;
    }
    if (!str) {
        return duration;
    }

    P = strchr(str, 'P');
    if (!P) {
	ldns_duration_cleanup(duration);
        return NULL;
    }

    T = strchr(str, 'T');
    X = strchr(str, 'Y');
    if (X) {
        duration->years = (time_t) atoi(str+1);
        str = X;
        not_weeks = 1;
    }
    X = strchr(str, 'M');
    if (X && (!T || (size_t) (X-P) < (size_t) (T-P))) {
        duration->months = (time_t) atoi(str+1);
        str = X;
        not_weeks = 1;
    }
    X = strchr(str, 'D');
    if (X) {
        duration->days = (time_t) atoi(str+1);
        str = X;
        not_weeks = 1;
    }
    if (T) {
        str = T;
        not_weeks = 1;
    }
    X = strchr(str, 'H');
    if (X && T) {
        duration->hours = (time_t) atoi(str+1);
        str = X;
        not_weeks = 1;
    }
    X = strrchr(str, 'M');
    if (X && T && (size_t) (X-P) > (size_t) (T-P)) {
        duration->minutes = (time_t) atoi(str+1);
        str = X;
        not_weeks = 1;
    }
    X = strchr(str, 'S');
    if (X && T) {
        duration->seconds = (time_t) atoi(str+1);
        str = X;
        not_weeks = 1;
    }

    W = strchr(str, 'W');
    if (W) {
        if (not_weeks) {
            ldns_duration_cleanup(duration);
            return NULL;
        } else {
            duration->weeks = (time_t) atoi(str+1);
            str = W;
        }
    }
    return duration;
}