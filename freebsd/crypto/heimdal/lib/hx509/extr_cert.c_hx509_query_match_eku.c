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
struct TYPE_3__ {int /*<<< orphan*/  match; int /*<<< orphan*/ * eku; } ;
typedef  TYPE_1__ hx509_query ;
typedef  int /*<<< orphan*/  heim_oid ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HX509_QUERY_MATCH_EKU ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int der_copy_oid (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  der_free_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

int
hx509_query_match_eku(hx509_query *q, const heim_oid *eku)
{
    int ret;

    if (eku == NULL) {
	if (q->eku) {
	    der_free_oid(q->eku);
	    free(q->eku);
	    q->eku = NULL;
	}
	q->match &= ~HX509_QUERY_MATCH_EKU;
    } else {
	if (q->eku) {
	    der_free_oid(q->eku);
	} else {
	    q->eku = calloc(1, sizeof(*q->eku));
	    if (q->eku == NULL)
		return ENOMEM;
	}
	ret = der_copy_oid(eku, q->eku);
	if (ret) {
	    free(q->eku);
	    q->eku = NULL;
	    return ret;
	}
	q->match |= HX509_QUERY_MATCH_EKU;
    }
    return 0;
}