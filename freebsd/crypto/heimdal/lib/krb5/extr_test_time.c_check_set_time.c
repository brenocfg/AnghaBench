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
struct timeval {scalar_t__ tv_sec; int /*<<< orphan*/  tv_usec; } ;
typedef  scalar_t__ krb5_timestamp ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*,int) ; 
 scalar_t__ krb5_set_real_time (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_us_timeofday (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
check_set_time(krb5_context context)
{
    krb5_error_code ret;
    krb5_timestamp sec;
    int32_t usec;
    struct timeval tv;
    int diff = 10;
    int diff2;

    gettimeofday(&tv, NULL);

    ret = krb5_set_real_time(context, tv.tv_sec + diff, tv.tv_usec);
    if (ret)
	krb5_err(context, 1, ret, "krb5_us_timeofday");

    ret = krb5_us_timeofday(context, &sec, &usec);
    if (ret)
	krb5_err(context, 1, ret, "krb5_us_timeofday");

    diff2 = abs(sec - tv.tv_sec);

    if (diff2 < 9 || diff > 11)
	krb5_errx(context, 1, "set time error: diff: %d",
		  abs(sec - tv.tv_sec));
}