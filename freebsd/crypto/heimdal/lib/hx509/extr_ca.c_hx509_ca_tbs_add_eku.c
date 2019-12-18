#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hx509_context ;
typedef  TYPE_2__* hx509_ca_tbs ;
typedef  int /*<<< orphan*/  heim_oid ;
struct TYPE_4__ {unsigned int len; int /*<<< orphan*/ * val; } ;
struct TYPE_5__ {TYPE_1__ eku; } ;

/* Variables and functions */
 int ENOMEM ; 
 int der_copy_oid (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ der_heim_oid_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 void* realloc (int /*<<< orphan*/ *,int) ; 

int
hx509_ca_tbs_add_eku(hx509_context context,
		     hx509_ca_tbs tbs,
		     const heim_oid *oid)
{
    void *ptr;
    int ret;
    unsigned i;

    /* search for duplicates */
    for (i = 0; i < tbs->eku.len; i++) {
	if (der_heim_oid_cmp(oid, &tbs->eku.val[i]) == 0)
	    return 0;
    }

    ptr = realloc(tbs->eku.val, sizeof(tbs->eku.val[0]) * (tbs->eku.len + 1));
    if (ptr == NULL) {
	hx509_set_error_string(context, 0, ENOMEM, "out of memory");
	return ENOMEM;
    }
    tbs->eku.val = ptr;
    ret = der_copy_oid(oid, &tbs->eku.val[tbs->eku.len]);
    if (ret) {
	hx509_set_error_string(context, 0, ret, "out of memory");
	return ret;
    }
    tbs->eku.len += 1;
    return 0;
}