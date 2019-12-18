#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  heim_oid ;
struct TYPE_8__ {int* version; TYPE_1__* extensions; } ;
struct TYPE_10__ {TYPE_2__ tbsCertificate; } ;
struct TYPE_9__ {int /*<<< orphan*/  extnID; } ;
struct TYPE_7__ {size_t len; TYPE_3__ const* val; } ;
typedef  TYPE_2__ TBSCertificate ;
typedef  TYPE_3__ Extension ;
typedef  TYPE_4__ Certificate ;

/* Variables and functions */
 scalar_t__ der_heim_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const Extension *
find_extension(const Certificate *cert, const heim_oid *oid, size_t *idx)
{
    const TBSCertificate *c = &cert->tbsCertificate;

    if (c->version == NULL || *c->version < 2 || c->extensions == NULL)
	return NULL;

    for (;*idx < c->extensions->len; (*idx)++) {
	if (der_heim_oid_cmp(&c->extensions->val[*idx].extnID, oid) == 0)
	    return &c->extensions->val[(*idx)++];
    }
    return NULL;
}