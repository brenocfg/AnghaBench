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
typedef  TYPE_1__* gss_OID ;
struct TYPE_4__ {scalar_t__ length; int /*<<< orphan*/  elements; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int
kgss_oid_equal(const gss_OID oid1, const gss_OID oid2)
{

	if (oid1 == oid2)
		return (1);
	if (!oid1 || !oid2)
		return (0);
	if (oid1->length != oid2->length)
		return (0);
	if (memcmp(oid1->elements, oid2->elements, oid1->length))
		return (0);
	return (1);
}