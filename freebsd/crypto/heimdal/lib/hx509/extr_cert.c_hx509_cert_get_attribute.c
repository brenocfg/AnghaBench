#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* hx509_cert_attribute ;
typedef  TYPE_3__* hx509_cert ;
typedef  int /*<<< orphan*/  heim_oid ;
struct TYPE_6__ {size_t len; TYPE_2__** val; } ;
struct TYPE_8__ {TYPE_1__ attrs; } ;
struct TYPE_7__ {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 scalar_t__ der_heim_oid_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

hx509_cert_attribute
hx509_cert_get_attribute(hx509_cert cert, const heim_oid *oid)
{
    size_t i;
    for (i = 0; i < cert->attrs.len; i++)
	if (der_heim_oid_cmp(oid, &cert->attrs.val[i]->oid) == 0)
	    return cert->attrs.val[i];
    return NULL;
}