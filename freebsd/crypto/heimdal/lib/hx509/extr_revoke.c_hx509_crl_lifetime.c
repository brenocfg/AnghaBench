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
typedef  TYPE_1__* hx509_crl ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_3__ {scalar_t__ expire; } ;

/* Variables and functions */
 scalar_t__ time (int /*<<< orphan*/ *) ; 

int
hx509_crl_lifetime(hx509_context context, hx509_crl crl, int delta)
{
    crl->expire = time(NULL) + delta;
    return 0;
}