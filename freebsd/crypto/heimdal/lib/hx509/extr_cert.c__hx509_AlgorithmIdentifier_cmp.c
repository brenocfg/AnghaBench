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
struct TYPE_4__ {scalar_t__ parameters; int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_1__ AlgorithmIdentifier ;

/* Variables and functions */
 int der_heim_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int heim_any_cmp (scalar_t__,scalar_t__) ; 

int
_hx509_AlgorithmIdentifier_cmp(const AlgorithmIdentifier *p,
			       const AlgorithmIdentifier *q)
{
    int diff;
    diff = der_heim_oid_cmp(&p->algorithm, &q->algorithm);
    if (diff)
	return diff;
    if (p->parameters) {
	if (q->parameters)
	    return heim_any_cmp(p->parameters,
				q->parameters);
	else
	    return 1;
    } else {
	if (q->parameters)
	    return -1;
	else
	    return 0;
    }
}