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
typedef  int /*<<< orphan*/  hx509_query ;
typedef  int /*<<< orphan*/  hx509_lock ;
typedef  int /*<<< orphan*/ * hx509_cert ;

/* Variables and functions */

int
_hx509_lock_find_cert(hx509_lock lock, const hx509_query *q, hx509_cert *c)
{
    *c = NULL;
    return 0;
}