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
struct TYPE_3__ {size_t length; unsigned int* components; } ;
typedef  TYPE_1__ heim_oid ;

/* Variables and functions */

__attribute__((used)) static size_t
len_oid (const heim_oid *oid)
{
    size_t ret = 1;
    size_t n;

    for (n = 2; n < oid->length; ++n) {
	unsigned u = oid->components[n];

	do {
	    ++ret;
	    u /= 128;
	} while(u > 0);
    }
    return ret;
}