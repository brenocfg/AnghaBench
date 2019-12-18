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
typedef  int /*<<< orphan*/  heim_oid ;

/* Variables and functions */
 int der_print_heim_oid (int /*<<< orphan*/  const*,char,char**) ; 

int
hx509_oid_sprint(const heim_oid *oid, char **str)
{
    return der_print_heim_oid(oid, '.', str);
}