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
struct _hx509_password {int dummy; } ;
typedef  TYPE_1__* hx509_lock ;
struct TYPE_3__ {struct _hx509_password const password; } ;

/* Variables and functions */

const struct _hx509_password *
_hx509_lock_get_passwords(hx509_lock lock)
{
    return &lock->password;
}