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
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_ca_tbs ;

/* Variables and functions */
 int hx509_ca_tbs_set_notAfter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

int
hx509_ca_tbs_set_notAfter_lifetime(hx509_context context,
				   hx509_ca_tbs tbs,
				   time_t delta)
{
    return hx509_ca_tbs_set_notAfter(context, tbs, time(NULL) + delta);
}