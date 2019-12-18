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
struct TYPE_3__ {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; int tm_usec; int tm_gmtoff; } ;
typedef  TYPE_1__ apr_time_exp_t ;

/* Variables and functions */
 int /*<<< orphan*/  apr_time_exp_lt (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_time_now () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void log_time()
{
    apr_time_exp_t tm;

    apr_time_exp_lt(&tm, apr_time_now());
    fprintf(stderr, "[%d-%02d-%02dT%02d:%02d:%02d.%06d%+03d] ",
            1900 + tm.tm_year, 1 + tm.tm_mon, tm.tm_mday,
            tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_usec,
            tm.tm_gmtoff/3600);
}