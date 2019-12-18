#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ starttime; scalar_t__ authtime; scalar_t__ endtime; scalar_t__ renew_till; } ;
typedef  TYPE_1__ krb5_times ;
typedef  int krb5_boolean ;

/* Variables and functions */

__attribute__((used)) static krb5_boolean
krb5_times_equal(const krb5_times *a, const krb5_times *b)
{
    return a->starttime == b->starttime &&
	a->authtime == b->authtime &&
	a->endtime == b->endtime &&
	a->renew_till == b->renew_till;
}