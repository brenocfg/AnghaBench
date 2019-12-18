#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  heim_oid ;
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
struct TYPE_5__ {size_t len; TYPE_2__ const* val; } ;
typedef  TYPE_1__ CMSAttributes ;
typedef  TYPE_2__ Attribute ;

/* Variables and functions */
 scalar_t__ der_heim_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const Attribute *
find_attribute(const CMSAttributes *attr, const heim_oid *oid)
{
    size_t i;
    for (i = 0; i < attr->len; i++)
	if (der_heim_oid_cmp(&attr->val[i].type, oid) == 0)
	    return &attr->val[i];
    return NULL;
}