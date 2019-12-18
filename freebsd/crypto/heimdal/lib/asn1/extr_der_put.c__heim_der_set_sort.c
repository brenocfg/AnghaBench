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
struct heim_octet_string {scalar_t__ length; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int
_heim_der_set_sort(const void *a1, const void *a2)
{
    const struct heim_octet_string *s1 = a1, *s2 = a2;
    int ret;

    ret = memcmp(s1->data, s2->data,
		 s1->length < s2->length ? s1->length : s2->length);
    if(ret)
	return ret;
    return s1->length - s2->length;
}