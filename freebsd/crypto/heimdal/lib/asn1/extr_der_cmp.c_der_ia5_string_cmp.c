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
typedef  int /*<<< orphan*/  heim_ia5_string ;

/* Variables and functions */
 int der_heim_octet_string_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

int
der_ia5_string_cmp(const heim_ia5_string *p,
		   const heim_ia5_string *q)
{
    return der_heim_octet_string_cmp(p, q);
}