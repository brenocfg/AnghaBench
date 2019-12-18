#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int len; TYPE_2__* val; } ;
struct TYPE_11__ {TYPE_3__ rdnSequence; } ;
struct TYPE_12__ {TYPE_4__ u; } ;
struct TYPE_9__ {int len; TYPE_1__* val; } ;
struct TYPE_8__ {int /*<<< orphan*/  value; int /*<<< orphan*/  type; } ;
typedef  TYPE_5__ Name ;

/* Variables and functions */
 int _hx509_name_ds_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int der_heim_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
_hx509_name_cmp(const Name *n1, const Name *n2, int *c)
{
    int ret;
    size_t i, j;

    *c = n1->u.rdnSequence.len - n2->u.rdnSequence.len;
    if (*c)
	return 0;

    for (i = 0 ; i < n1->u.rdnSequence.len; i++) {
	*c = n1->u.rdnSequence.val[i].len - n2->u.rdnSequence.val[i].len;
	if (*c)
	    return 0;

	for (j = 0; j < n1->u.rdnSequence.val[i].len; j++) {
	    *c = der_heim_oid_cmp(&n1->u.rdnSequence.val[i].val[j].type,
				  &n1->u.rdnSequence.val[i].val[j].type);
	    if (*c)
		return 0;

	    ret = _hx509_name_ds_cmp(&n1->u.rdnSequence.val[i].val[j].value,
				     &n2->u.rdnSequence.val[i].val[j].value,
				     c);
	    if (ret)
		return ret;
	    if (*c)
		return 0;
	}
    }
    *c = 0;
    return 0;
}