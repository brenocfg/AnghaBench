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
typedef  TYPE_1__* hx509_name ;
struct TYPE_4__ {int /*<<< orphan*/  der_name; } ;

/* Variables and functions */
 int _hx509_name_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

int
hx509_name_cmp(hx509_name n1, hx509_name n2)
{
    int ret, diff;
    ret = _hx509_name_cmp(&n1->der_name, &n2->der_name, &diff);
    if (ret)
	return ret;
    return diff;
}