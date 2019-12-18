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
typedef  TYPE_2__* hx509_request ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  heim_oid ;
struct TYPE_4__ {int len; int /*<<< orphan*/ * val; } ;
struct TYPE_5__ {TYPE_1__ eku; } ;

/* Variables and functions */
 int ENOMEM ; 
 int der_copy_oid (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 void* realloc (int /*<<< orphan*/ *,int) ; 

int
_hx509_request_add_eku(hx509_context context,
		       hx509_request req,
		       const heim_oid *oid)
{
    void *val;
    int ret;

    val = realloc(req->eku.val, sizeof(req->eku.val[0]) * (req->eku.len + 1));
    if (val == NULL)
	return ENOMEM;
    req->eku.val = val;

    ret = der_copy_oid(oid, &req->eku.val[req->eku.len]);
    if (ret)
	return ret;

    req->eku.len += 1;

    return 0;
}